<?php


namespace Demo\CLI\Deprecated\Event;


use Demo\CLI\Event\Event;
use Tiny\Event\EventCenterAutoRegistrator;
use Tiny\Event\Listener;

class AutoRegistrator extends EventCenterAutoRegistrator {

  /**
   * 返回要自动注册的Listener
   * @return Listener
   */
  protected function listener(): Listener {
    return new \Demo\CLI\Event\Listener(new Event(10, "EventCenterAutoRegistrator - 10"));
  }
}

class AutoRegistrator2 extends EventCenterAutoRegistrator {

  /**
   * 返回要自动注册的Listener
   * @return Listener
   */
  protected function listener(): Listener {
    $event = new Event(14, "EventCenterAutoRegistrator - all");
    $event->toAll();
    return new \Demo\CLI\Event\Listener($event);
  }
}