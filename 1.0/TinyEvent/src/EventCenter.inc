<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/30
 * Time: 下午7:58
 */

namespace Tiny\Event;


use Tiny\Event\Center\AutoEventData;
use Tiny\Event\Center\DefaultName;
use Tiny\Event\Center\Name;
use Tiny\Logger;

class EventCenter {

  public function __construct(Name $name) {
    $this->name_ = $name;
  }

  static public function default() {
    return new EventCenter(DefaultName::to());
  }

  static public function byName(Name $name) {
    return new EventCenter($name);
  }

//  public function addListener(Listener $listener) {
//    $listener->getEvent()->addHandler($listener->getClassSign());
//  }
//
//  public function removeListener(Listener $listener) {
//    $listener->getEvent()->removeHandler($listener->getClassSign());
//  }
//
//  public function postEvent(Event $event):bool {
//    $result = true;
//    /**
//     * @var $handlers array[['event'=>Event, 'handlers'=>[]], ...]
//     */
//    $event_handlers = $event->getHandlers();
//
//    foreach ($event_handlers as $event_handler) {
//      foreach ($event_handler['handlers'] as $handler) {
//        Logger::getInstance()->debug("postEvent response: Event("
//          .$event_handler['event']->getId()
//          .")--->Listener(".$handler.")");
//        $listener = Listener::New($handler, $event_handler['event']);
//        $result = $result && $listener->process();
//      }
//    }
//
//    return $result;
//  }

  public function postEvent(Event $event):bool {
    $ids = $event->getAllMayBeIds();
    $handlers = [];
    $ret = true;

    foreach ($ids as $id) {
      $handlers = array_merge($handlers
        , AutoEventData::getHandlerForName($id, $this->name_));
    }

    foreach ($handlers as $handler) {
      Logger::getInstance()->debug("postEvent: Event("
          .$event->getId()
          .")--->Listener(".$handler.")");
      $listener = Listener::New($handler, $event);
      $ret = $ret && $listener->process();
    }

    return $ret;
  }

//  public function postTimerEvent() {
//    $this->postEvent(new TimerEvent(0, [], ""));
//  }

  /**
   * @var Name
   */
  private $name_;
}

