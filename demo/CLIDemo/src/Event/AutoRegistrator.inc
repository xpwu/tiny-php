<?php


namespace Demo\CLI\Event;


use Tiny\Event\Center\DefaultName;
use Tiny\Event\EventCenter;
use Tiny\Event\Listener;
use Tiny\Event\ListeningMode;

class AutoRegistrator implements \Tiny\Event\Center\Annotation\AutoRegistrator {

  function registerToEventCenter(): EventCenter {
    return EventCenter::default();
  }

  function addListeners(EventCenter $eventCenter): void {
    $eventCenter->addListener(new \Demo\CLI\Event\Listener(
      new Event(10, (string)DefaultName::toName())));
    $eventCenter->addListener(new \Demo\CLI\Event\Listener(
      new Event(5, (string)DefaultName::toName())));
  }
}

class AutoRegistrator2 implements \Tiny\Event\Center\Annotation\AutoRegistrator {

  function registerToEventCenter(): EventCenter {
    return EventCenter::byName(Named::toName());
  }

  function addListeners(EventCenter $eventCenter): void {
    $eventCenter->addListener(new \Demo\CLI\Event\Listener(
      new Event(10, (string)Named::toName())));
    $eventCenter->addListener(new \Demo\CLI\Event\Listener(
      new Event(5, (string)Named::toName())));
  }
}

class AutoRegistrator3 implements \Tiny\Event\Center\Annotation\AutoRegistrator {

  function registerToEventCenter(): EventCenter {
    return EventCenter::byName(Named::toName());
  }

  function addListeners(EventCenter $eventCenter): void {
    $eventCenter->addListenerWithMode(new \Demo\CLI\Event\Listener(
      new Event(0, (string)Named::toName())), ListeningMode::notUseEventArgs());
  }
}
