<?php


namespace Tiny\DBIndex\Annotation\Processor;


use Inte\Annotation\AbstractAnnotationServer;
use Inte\Annotation\Config;
use Inte\Annotation\Logger;
use Inte\Annotation\PhpFiler;
use Tiny\Core\Utils;
use Tiny\DB\Index\Annotation\AllNeedCreateIndex;
use Tiny\DB\Index\Annotation\NeedCreateIndex;

class NeedCreateIndexProcessor extends AbstractAnnotationServer {

  /**
   * @param string[] $classes
   * @throws \ReflectionException
   */
  function process(array $classes): void {
    if (!$this->isBuild_) {
      return;
    }

    foreach ($classes as $class) {
      $clazz = new \ReflectionClass($class);
      if ($clazz->isSubclassOf(NeedCreateIndex::class)
        && !$clazz->isAbstract() && !$clazz->isInterface()) {
        $this->all_[] = $class;
      }
    }

    $this->write();
  }


  /**
   * @param array $dependencyClasses
   * @throws \ReflectionException
   */
  public function processDependencyClasses(array $dependencyClasses): void {
    if (!$this->isBuild_) {
      return;
    }

    foreach ($dependencyClasses as $dependencyClass) {
      $clazz = new \ReflectionClass($dependencyClass);
      if ($clazz->isSubclassOf(NeedCreateIndex::class)
        && !$clazz->isAbstract() && !$clazz->isInterface()) {
        $this->all_[] = $dependencyClass;
      }
    }

    $this->write();
  }

  private function write() {
    $fileName = AllNeedCreateIndex::getFileDirAndName();
    $className = AllNeedCreateIndex::getCreatedClassName();
    $nameSpace = AllNeedCreateIndex::getNameSpace();
    $superClass = AllNeedCreateIndex::getSuperShortClassName();
    $all = Utils::stringArray2string($this->all_);

    $content = <<<EOF
<?php

namespace $nameSpace;

use Tiny\Logger;

class $className extends $superClass {

  private \$all = [$all];
  
  /**
   * @return NeedCreateIndex[]
   */
  public function getAll():array  {
    \$ret = [];
    foreach (\$this->all as \$index) {
      try {
        \$ref = new \ReflectionClass(\$index);
      } catch (\ReflectionException \$e) {
        Logger::getInstance()->error("按道理不应该找不到这个类", \$e);
        continue;
      }
      \$ret[] = \$ref->newInstanceWithoutConstructor();
    }
    
    return \$ret;
  }
}

EOF;

    $writer = $this->filer_->createSourceFile($fileName);

    $writer->rewrite($content);
  }


  function init(Logger $logger, PhpFiler $filer
    , Config $config, string $projectRootDir, bool $isBuild): void {
    $this->isBuild_ = $isBuild;
    $this->logger_ = $logger;
    $this->filer_ = $filer;
  }

  private $isBuild_;
  private $logger_;
  /**
   * @var PhpFiler
   */
  private $filer_;
  /**
   * @var string[]
   */
  private $all_ = [];

}