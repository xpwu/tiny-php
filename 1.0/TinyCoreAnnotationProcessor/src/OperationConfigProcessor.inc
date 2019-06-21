<?php


namespace Tiny\Core\Annotation\Processor;


use Inte\Annotation\AbstractAnnotationServer;
use Inte\Annotation\Config;
use Inte\Annotation\Helper;
use Inte\Annotation\Logger;
use Inte\Annotation\PhpFiler;
use ReflectionClass;
use Tiny\Core\Annotation\ConfigGroup;
use Tiny\Core\Annotation\OperationConfig;

/**
 * Class OperationConfigProcessor
 * @package Tiny\Core\Annotation\Processor
 */
class OperationConfigProcessor extends AbstractAnnotationServer {

  /**
   * @param string[] $classes
   * @throws \ReflectionException
   */
  function process(array $classes): void {
    /**
     * @var ReflectionClass
     */
//    $allConfigs = [];
//    $helper = new Helper(new ReflectionClass(OperationConfig::class)
//      , $this->logger_);

    foreach ($classes as $class) {
      $refClass = new ReflectionClass($class);
      if (!$this->helper_->isAnnotatingClass($refClass)) {
        continue;
      }

      $this->checkConfigNotComment($refClass);

      $this->processClass($refClass);
    }

//    foreach ($allConfigs as $config) {
//      $this->checkConfig($config);
//    }
//
//    $this->createConfig($allConfigs);

    if (count($classes) === 0) {
      $this->writeConfigWithGroup();
    }
  }

  /**
   * @param array $dependencyClasses
   * @throws \ReflectionException
   */
  public function processDependencyClasses(array $dependencyClasses): void {
    /**
     * @var ReflectionClass
     */
//    $allConfigs = [];
//    $helper = new Helper(new ReflectionClass(OperationConfig::class)
//      , $this->logger_);

    foreach ($dependencyClasses as $class) {
      $refClass = new ReflectionClass($class);
      if (!$this->helper_->isAnnotatingClass($refClass)) {
        continue;
      }

      $this->processClass($refClass);
    }

//    $this->createConfig($allConfigs);
  }

  /**
   * @param ReflectionClass $refClass
   * @throws \ReflectionException
   */
  private function processClass(ReflectionClass $refClass):void {
    $tokenizer = Helper\Tokenizer::createTokenizer($refClass);
    $allImpls = $tokenizer->getAllImplements();
    $name = "~~~~~~~~~~~~";
    foreach ($allImpls as $impl) {
      $clazz = new ReflectionClass($impl);
      if (!$this->group_->isAnnotatingClass($clazz)) {
        continue;
      }
      $name = $clazz->getShortName();
      break;
    }
    $last = @$this->allConfigs_[$name] ?? [];
    $last[] = $refClass;

    $this->allConfigs_[$name] = $last;
  }

  private function writeConfigWithGroup():void {
    $content = $this->content_;
    foreach ($this->allConfigs_ as $name=>$items) {
      /**
       * @var ReflectionClass[] $items
       */
      $content .= $this->createGroupConfig($name, ...$items);
    }

    $writer = $this->filer_->createSourceFile("operation_config.php");
    $writer->rewrite($content);
  }

  private function createGroupConfig(string $groupName
    , ReflectionClass ...$classes):string {
    $ret = PHP_EOL
      . "// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ $groupName ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      . PHP_EOL;

    foreach ($classes as $class) {
      $ret .= $this->createAConfig($class) . PHP_EOL;
    }

    return $ret . PHP_EOL;
  }

  private function createAConfig(ReflectionClass $class):string {
    $ns = $class->getNamespaceName();
    $className = $class->getShortName();
    $classDoc = $this->getDoc($class->getDocComment()
      , "", 'Interface', 'Class', '@');

    $content = <<<EOF

${classDoc}namespace $ns {class $className {

EOF;

    foreach ($class->getReflectionConstants() as $reflectionConstant) {
      $name = $reflectionConstant->getName();
      $value = $this->valueToString($reflectionConstant->getValue(), "\t");
      $doc = $this->getDoc($reflectionConstant->getDocComment()
        , "\t", '@');

      $content .= <<<EOF
  ${doc}public const $name = $value;

EOF;

    }

    $content .= <<<EOF
}}
EOF;
    return $content;
  }

  private function getDoc($comment, string $prefix = "", string ...$excludes):string {
    if ($comment !== false) {
      $comment = new Helper\Comment($comment);
      $classDoc = implode(PHP_EOL. $prefix, array_map(
        function ($value) use ($prefix) {
        return '// ' . $value;
      }, $comment->exclude(...$excludes)));
      if ($classDoc !== "") {
        $classDoc .= PHP_EOL . $prefix;
      }
    } else {
      $classDoc = "";
    }

    return $classDoc;
  }

  /**
   * @param ReflectionClass[] $classes
   */
  private function createConfigNoGroup(array $classes):void {

    foreach ($classes as $reflectionClass) {
      $nameSpace  = $reflectionClass->getNamespaceName();
      $className = $reflectionClass->getShortName();
      $classDoc = $reflectionClass->getDocComment();

      $ns = <<<EOF

namespace $nameSpace {

EOF;

      $content = <<<EOF
      
$classDoc
interface $className {

EOF;

      $constant = "";
      foreach ($reflectionClass->getReflectionConstants() as $reflectionConstant) {
        $name = $reflectionConstant->getName();
        $value = $this->valueToString($reflectionConstant->getValue(), "\t\t");
        $doc = $reflectionConstant->getDocComment();

        $constant = $constant.<<<EOF
    
  $doc
  public const $name = $value;
    
EOF;

      }

      $content = $content.$constant.<<<EOF
      
}
EOF;
      $content = str_replace("\n", "\n\t", $content);

      $nsEnd = <<<EOF
      
}


EOF;


      $this->content_ = $this->content_ . $ns . $content . $nsEnd;
    }
  }

  private function valueToString($value, string $prefix = ""):string {
    if (is_string($value)) {
      return "'" . $value . "'";
    }

    if (is_bool($value)) {
      return $value?'true':'false';
    }

    // 根据前面检查的逻辑，这里可能为：int float
    if (!is_array($value)) {
      return (string)$value;
    }

    $arr = "[";
    foreach ($value as $key=>$val) {
      if (is_int($key)) {
        $arr = $arr . PHP_EOL . $prefix
          . $this->valueToString($val, $prefix . "\t")
          . ",";
        continue;
      }

      $arr = $arr . PHP_EOL . $prefix . "'" . $key . "' => "
        . $this->valueToString($val, $prefix . "\t") . ",";
    }
    $arr = $arr . PHP_EOL . $prefix . "]";

    return $arr;
  }

  private function checkConfigNotComment(ReflectionClass $class):void {
    $classInfo = $this->info($class);

    if (!$class->isInterface()) {
      $this->logger_->throwError(
        "$classInfo is not 'interface', 'Config' must be a 'interface'");
    }

//    if ($class->getDocComment() === false) {
//      $this->logger_->throwError(
//        "$classInfo has not 'comment', it is needed");
//    }

    if (count($class->getMethods()) != 0) {
      $this->logger_->throwError(
        "$classInfo can NOT define method, only public const is valid");
    }

    /**
     * @var \ReflectionClassConstant[]
     */
    $allConstants = $class->getReflectionConstants();
    foreach ($allConstants as $constant) {
      $name = $constant->getName();

//      if ($constant->getDocComment() === false) {
//        $this->logger_->throwError(
//          "'$name' has not 'comment' in $classInfo, it is needed");
//      }

      // interface 一定是public， 所以这里不再判断
//      if (!$constant->isPublic()) {
//        $this->logger_->throwError(
//          "$name in $classInfo is not public, only public const is valid");
//      }

      $value = $constant->getValue();
      if (!$this->isValidValue($value)) {
        $this->logger_->throwError(
          "type of $name in $classInfo is invalid, "
          . "only string, int, float, string[], int[], float[] or array[] are valid");
      }
    }
  }

  private function checkConfig(ReflectionClass $class):void {
    $classInfo = $this->info($class);

    if (!$class->isInterface()) {
      $this->logger_->throwError(
        "$classInfo is not 'interface', 'Config' must be a 'interface'");
    }

    if ($class->getDocComment() === false) {
      $this->logger_->throwError(
        "$classInfo has not 'comment', it is needed");
    }

    if (count($class->getMethods()) != 0) {
      $this->logger_->throwError(
        "$classInfo can NOT define method, only public const is valid");
    }

    /**
     * @var \ReflectionClassConstant[]
     */
    $allConstants = $class->getReflectionConstants();
    foreach ($allConstants as $constant) {
      $name = $constant->getName();

      if ($constant->getDocComment() === false) {
        $this->logger_->throwError(
          "'$name' has not 'comment' in $classInfo, it is needed");
      }

      // interface 一定是public， 所以这里不再判断
//      if (!$constant->isPublic()) {
//        $this->logger_->throwError(
//          "$name in $classInfo is not public, only public const is valid");
//      }

      $value = $constant->getValue();
      if (!$this->isValidValue($value)) {
        $this->logger_->throwError(
          "type of $name in $classInfo is invalid, "
          . "only string, int, float, string[], int[], float[] or array[] are valid");
      }
    }
  }

  private function isValidValue($value):bool {
    if (is_int($value) || is_float($value)
      || is_string($value) || is_bool($value)) {
      return true;
    }

    if (is_array($value)) {
      foreach ($value as $item) {
        if (!$this->isValidValue($item)) {
          return false;
        }
      }
      return true;
    }

    return false;
  }

  private function info(ReflectionClass $class):string {
    return $class->getName() . "(" . $class->getFileName() . ")";
  }

  function init(Logger $logger, PhpFiler $filer
    , Config $config, string $projectRootDir, bool $isBuild): void {
    $this->isBuild_ = $isBuild;
    $this->logger_ = $logger;
    $this->filer_ = $filer;
    $this->helper_ = new Helper(new ReflectionClass(OperationConfig::class)
      , $this->logger_);
    $this->group_ = new Helper(new ReflectionClass(ConfigGroup::class)
      , $this->logger_);
  }

  /**
   * @var Helper
   */
  private $group_;
  /**
   * @var Helper
   */
  private $helper_;
  /**
   * @var ReflectionClass[][]
   */
  private $allConfigs_ = [];

  private $isBuild_;
  /**
   * @var Logger
   */
  private $logger_;
  /**
   * @var PhpFiler
   */
  private $filer_;
  /**
   * @var string
   */
  private $content_ = <<<EOF
<?php

// - Operation Config -

EOF;


}