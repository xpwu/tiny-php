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
  function __construct(Event $event) {
    $this->event_ = $event;
  }

  public function getClassSign() {
    return get_class($this);
  }

  static public function New(string $classSign, Event $event):Listener {
    return new $classSign($event);
  }

  abstract protected function handler();

  public function process() {
    try {
      $this->handler();
    } catch (\Exception $e) {
      Logger::getInstance()->error($this->event_->getId()
        ."+".Listener::getClassSign()." error!", $e);

      $this->event_->handlerError();
      return;
    }
    Logger::getInstance()->debug($this->event_->getId()
      ."+".Listener::getClassSign()." success!");

    $this->event_->handlerOver();
  }

  public function getEvent():Event {
    return $this->event_;
  }

  private $event_;
}
