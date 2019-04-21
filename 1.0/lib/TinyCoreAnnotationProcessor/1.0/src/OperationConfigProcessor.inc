<?php


namespace Tiny\Annotation\Processor;


use Inte\Annotation\AbstractAnnotationServer;
use Inte\Annotation\Config;
use Inte\Annotation\Logger;
use Inte\Annotation\PhpFiler;
use ReflectionClass;
use Tiny\Core\Annotation\OperationConfig;

class OperationConfigProcessor extends AbstractAnnotationServer {

  /**
   * @param string[] $classes
   * @throws \ReflectionException
   */
  function process(array $classes): void {
    /**
     * @var ReflectionClass
     */
    $allConfigs = [];
    foreach ($classes as $class) {
      $refClass = new ReflectionClass($class);
      if ($refClass->isSubclassOf(OperationConfig::class)) {
        $allConfigs[] = $refClass;
      }
    }

    foreach ($allConfigs as $config) {
      $this->checkConfig($config);
    }

    $this->createConfig($allConfigs);

    if (count($classes) === 0) {
      $writer = $this->filer_->createSourceFile("operation_config.php");
      $writer->rewrite($this->content_);
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
    $allConfigs = [];
    foreach ($dependencyClasses as $class) {
      $refClass = new ReflectionClass($class);
      if ($refClass->isSubclassOf(OperationConfig::class)) {
        $allConfigs[] = $refClass;
      }
    }

    $this->createConfig($allConfigs);
  }

  /**
   * @param ReflectionClass[] $classes
   */
  private function createConfig(array $classes):void {

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
      || is_string($value)) {
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
  }

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

// ------ Operation Config ------

EOF;


}