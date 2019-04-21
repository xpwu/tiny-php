<?php


namespace Tiny;


use Inte\Annotation\AbstractAnnotationServer;
use Inte\Annotation\Config;
use Inte\Annotation\Logger;
use Inte\Annotation\PhpFiler;
use Tiny\CLI\Annotation\AllCLIAnnotation;
use Tiny\Core\Utils;


class CLIAnnotationProcessor extends AbstractAnnotationServer {

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
      if ($clazz->isSubclassOf(CLIAnnotation::class)
        && !$clazz->isAbstract() && !$clazz->isInterface()) {
        $this->allCli_[] = $class;
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
      if ($clazz->isSubclassOf(CLIAnnotation::class)
        && !$clazz->isAbstract() && !$clazz->isInterface()) {
        $this->allCli_[] = $dependencyClass;
      }
    }

    $this->write();
  }

  private function write() {
    $fileName = AllCLIAnnotation::getFileDirAndName();
    $className = AllCLIAnnotation::getCreatedClassName();
    $nameSpace = AllCLIAnnotation::getNameSpace();
    $superClass = AllCLIAnnotation::getSuperShortClassName();
    $all = Utils::stringArray2string($this->allCli_);

    $content = <<<EOF
<?php

namespace $nameSpace;

use Tiny\CLIAnnotation;

class $className extends $superClass {

  private \$all = [$all];
  
  /**
   * @return CLIAnnotation[]
   */
  public function getAllCLIAnnotation():array {
    \$ret = [];
    foreach (\$this->all as \$cli) {
      \$ret[] = new \$cli();
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
  private $allCli_ = [];
}