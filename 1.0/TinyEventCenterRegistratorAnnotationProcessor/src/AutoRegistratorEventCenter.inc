<?php


namespace Tiny\Event\Annotation\Processor;


use Tiny\Event\Center\DefaultName;
use Tiny\Event\EventCenter;
use Tiny\Event\Listener;
use Tiny\Event\ListeningMode;

class AutoRegistratorEventCenter extends EventCenter {
  public function addListenerWithMode(Listener $listener, ListeningMode $mode) {
    $this->listeners_[] = $listener;
    $mode->adjustEventSafely($listener->getEvent());
  }

  static public function defaultAuto():AutoRegistratorEventCenter {
    return new AutoRegistratorEventCenter(DefaultName::toName());
  }

  /**
   * @return Listener[]
   */
  public function getAllListeners():array {
    return $this->listeners_;
  }

  private $listeners_ = [];
}