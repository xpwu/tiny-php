<?php


namespace Tiny\Event\CenterRegistrator\Annotation\Processor;


use Inte\Annotation\AbstractAnnotationServer;
use Inte\Annotation\Config;
use Inte\Annotation\Helper;
use Inte\Annotation\Logger;
use Inte\Annotation\PhpFiler;
use Tiny\Core\Utils;
use Tiny\Event\Center\Annotation\AutoRegistrator;
use Tiny\Event\Center\AutoRegistratorHelper;
use Tiny\Event\EventCenter;
use Tiny\Event\Listener;

class AutoRegistratorProcessor extends AbstractAnnotationServer {

  /**
   * @param string[] $classes
   * @throws \ReflectionException
   */
  function process(array $classes): void {
    if (!$this->isBuild_) {
      return;
    }

    $this->processClasses($classes);

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

    $this->processClasses($dependencyClasses);

    $this->write();
  }

  /**
   * @param array $classes
   * @throws \ReflectionException
   */
  private function processClasses(array $classes):void {
    $annotationHelper = new Helper(
      new \ReflectionClass(AutoRegistrator::class), $this->logger_);
    foreach ($classes as $class) {
      $clazz = new \ReflectionClass($class);
      if ($annotationHelper->isAnnotatingClass($clazz)
        && !$clazz->isAbstract() && !$clazz->isInterface()) {
        /**
         * @var $autoRegistrator AutoRegistrator
         */
        $autoRegistrator = new $class;
        $ec = $autoRegistrator->registerToEventCenter();
        $tmpEc = AutoRegistratorEventCenter::defaultAuto();
        $autoRegistrator->addListeners($tmpEc);

        $listeners = $tmpEc->getAllListeners();
        foreach ($listeners as $listener) {
          $this->register($ec, $listener);
        }
      }
    }
  }

  private function register(EventCenter $center, Listener $listener):void {
    $name = $center->getName()->__toString();
    $eventId = $listener->getEvent()->getId()->__toString();
    $listenerClassSing = $listener->getClassSign()->__toString();

    $eventMap = @$this->nameEventMap_[$name];
    if (!isset($eventMap)) {
      $eventMap = [];
    }

    /**
     * @var $classSigns string[]
     */
    $classSigns = @$eventMap[$eventId];
    if (!isset($classSigns)) {
      $classSigns = [];
    }

    $classSigns[] = $listenerClassSing;
    $eventMap[$eventId] = array_unique($classSigns);
    $this->nameEventMap_[$name] = $eventMap;
  }

  private function write():void {
    foreach ($this->nameEventMap_ as $name => $eventMap) {
      $fileName = AutoRegistratorHelper::getFileDirAndName($name);
      $className = AutoRegistratorHelper::getCreatedClassName($name);
      $nameSpace = AutoRegistratorHelper::getNameSpace($name);
      $superClass = "\\" . AutoRegistratorHelper::class;

      $content = <<< EOF
<?php

namespace $nameSpace;

use Tiny\Event\EventID;
use Tiny\Event\ListenerClassSign;

class $className extends $superClass {
  /**
   * @return ListenerClassSign[]
   */
  public function getAllListenerClassSignByEventID(EventID \$eventId):array {
    \$id = \$eventId->__toString();
    
    if (!array_key_exists(\$id, \$this->all_)) {
      return [];
    }
    
    \$ret = [];
    foreach (\$this->all_[\$id] as \$item) {
      \$ret[] = new ListenerClassSign(\$item);
    }
    return \$ret;
  }
  
  private \$all_ = [

EOF;

      foreach ($eventMap as $eventId => $listenerClassSigns) {
        $content = $content
          . "\t\t\"" . $eventId . "\" => ["
            . Utils::stringArray2string($listenerClassSigns)
            . "]," . PHP_EOL;
      }

      $content = $content.<<<EOF
  ];
  
}
EOF;

      $writer = $this->filer_->createSourceFile($fileName);

      $writer->rewrite($content);

    }
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
   * @var [name=>[eventId=>[listenerClassSign]]]
   */
  private $nameEventMap_ = [];
}