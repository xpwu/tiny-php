<?php


namespace Demo\CLI\Event;


use Tiny\Event\EventCenter;
use Tiny\Event\Listener;

class AutoRegistrator implements \Tiny\Event\Center\Annotation\AutoRegistrator {

  /**
   * @return Listener[]
   */
  function needRegisterListeners(): array {
    return [new \Demo\CLI\Event\Listener(new Event(10, 100)),
      new \Demo\CLI\Event\Listener(new Event(5, 25))];
  }

  function registerToEventCenter(): EventCenter {
    return EventCenter::default();
  }
}

class AutoRegistrator2 implements \Tiny\Event\Center\Annotation\AutoRegistrator {

  /**
   * @return Listener[]
   */
  function needRegisterListeners(): array {
    return [new \Demo\CLI\Event\Listener(new Event(10, 150)),
      new \Demo\CLI\Event\Listener(new Event(5, 25))];
  }

  function registerToEventCenter(): EventCenter {
    return EventCenter::byName(Named::toName());
  }
}

class AutoRegistrator3 implements \Tiny\Event\Center\Annotation\AutoRegistrator {

  /**
   * @return Listener[]
   */
  function needRegisterListeners(): array {
    $event = new Event(0, 0);
    $event->toAll();
    return [new \Demo\CLI\Event\Listener($event)];
  }

  function registerToEventCenter(): EventCenter {
    return EventCenter::byName(Named::toName());
  }
}
