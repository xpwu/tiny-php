<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/29
 * Time: 下午11:13
 */

namespace Tiny\Event;


use Tiny\Logger;

abstract class Listener {
  /**
   * Listener constructor.
   * @param Event $event
   */
  function __construct(Event $event) {
    $this->event_ = $event;
  }

  public function getClassSign():ListenerClassSign {
    return new ListenerClassSign(get_class($this));
  }

  static public function New(ListenerClassSign $classSign, Event $event):Listener {
    $clazz = $classSign->__toString();
    return new $clazz($event);
  }

  abstract protected function handler();

  public function process():bool {
    try {
      $this->handler();
    } catch (\Exception $e) {
      Logger::getInstance()->error($this->event_->getId()
        ."+".Listener::getClassSign()." error!", $e);

      $this->event_->handlerError();
      return false;
    }
    Logger::getInstance()->debug($this->event_->getId()
      ."+".Listener::getClassSign()." success!");

    $this->event_->handlerOver();
    return true;
  }

  public function getEvent():Event {
    return $this->event_;
  }

  private $event_;
}
