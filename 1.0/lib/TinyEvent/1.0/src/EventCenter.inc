<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/30
 * Time: 下午7:58
 */

namespace Tiny\Event;


use Tiny\Event\Center\AutoRegistratorHelper;
use Tiny\Event\Center\DefaultName;
use Tiny\Event\Center\Name;
use Tiny\Logger;

class EventCenter {

  protected function __construct(Name $name) {
    $this->name_ = $name;
  }

  static public function default():EventCenter {
    return new EventCenter(DefaultName::toName());
  }

  static public function byName(Name $name):EventCenter {
    return new EventCenter($name);
  }

  /**
   * @param Listener $listener
   * @param ListeningMode $mode
   *
   * 为了与原来的兼容，调用event->toAll 后，这里即使使用 useEventArgs Mode, 也仍然会按照
   * notUseEventArgs 的方式运行
   *
   */
  public function addListenerWithMode(Listener $listener, ListeningMode $mode) {
    // todo: 默认实现为动态注册 这里不实现不影响自动注册，仍可调用
//    $listener->getEvent()->addHandler($listener->getClassSign());
  }

  public function addListener(Listener $listener) {
    $this->addListenerWithMode($listener, ListeningMode::useEventArgs());
  }

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
    /**
     * @var ListenerClassSign[]
     */
    $listenerClassSigns = [];
    $ret = true;

    $helper = AutoRegistratorHelper::getRegistratorHelper($this->name_);

    foreach ($ids as $id) {
      $listenerClassSigns = array_merge($listenerClassSigns
        , $helper->getAllListenerClassSignByEventID($id));
    }

    // 相同的监听者  只是发一次，  可能出现All 与 带参数的事件都监听了
    $listenerClassSigns = array_unique($listenerClassSigns);

    /**
     * @var $listenerClassSign ListenerClassSign
     */
    foreach ($listenerClassSigns as $listenerClassSign) {
      Logger::getInstance()->debug("postEvent: Event("
          .$event->getId()
          .")--->Listener(" . $listenerClassSign .")");

      $listener = Listener::New($listenerClassSign, $event);

      $ret = $ret && $listener->process();
    }

    return $ret;
  }

  public function getName():Name {
    return $this->name_;
  }

//  public function postTimerEvent() {
//    $this->postEvent(new TimerEvent(0, [], ""));
//  }

  /**
   * @var Name
   */
  private $name_;
}

