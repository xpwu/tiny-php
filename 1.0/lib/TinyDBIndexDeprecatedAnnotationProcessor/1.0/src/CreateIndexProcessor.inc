<?php


namespace Tiny\DBIndex\Deprecated\Annotation\Processor;


use Inte\Annotation\AbstractAnnotationServer;
use Inte\Annotation\Config;
use Inte\Annotation\Helper;
use Inte\Annotation\Logger;
use Inte\Annotation\PhpFiler;
use Tiny\Core\Utils;
use Tiny\DB\CreateIndexInterface;
use Tiny\Deprecated\Annotation\AllOldCreateIndexInterfaceHelper;

class CreateIndexProcessor extends AbstractAnnotationServer {
  /**
   * @param string[] $classes
   * @throws \ReflectionException
   */
  function process(array $classes): void {
    $this->processClasses($classes);
  }


  /**
   * @param string[] $dependencyClasses
   * @throws \ReflectionException
   */
  public function processDependencyClasses(array $dependencyClasses): void {
    $this->processClasses($dependencyClasses);
  }

  /**
   * @param array $classes
   * @throws \ReflectionException
   */
  private function processClasses(array $classes):void {
    if (!$this->isBuild_) {
      return;
    }

    $helper = new Helper(
      new \ReflectionClass(CreateIndexInterface::class), $this->logger_);
    foreach ($classes as $class) {
      $clazz = new \ReflectionClass($class);
      if ($helper->isAnnotatingClass($clazz)
        && !$clazz->isAbstract() && !$clazz->isInterface()) {
        $this->all_[] = $class;
      }
    }

    $this->write();
  }

  private function write() {
    if (count($this->all_) === 0) {
      return;
    }

    $fileName = AllOldCreateIndexInterfaceHelper::getFileDirAndName();
    $className = AllOldCreateIndexInterfaceHelper::getCreatedClassName();
    $nameSpace = AllOldCreateIndexInterfaceHelper::getNameSpace();
    $superClass = AllOldCreateIndexInterfaceHelper::getSuperShortClassName();
    $all = Utils::stringArray2string($this->all_);

    $content = <<<EOF
<?php

namespace $nameSpace;

class $className extends $superClass {

  private \$all = [$all];
  
  /**
   * @return string[]
   */
  protected function getAll():array  {
    
    return \$this->all;
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