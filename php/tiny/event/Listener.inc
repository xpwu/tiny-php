<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/29
 * Time: 下午11:13
 */

namespace Tiny\Event;


abstract class Listener {
  function __construct(Event $event) {
    $this->event_ = $event;
  }

  public function getClassSign() {
    return get_class($this);
  }

  static public function New(string $classSign, Event $event):Listener {
    return $classSign($event);
  }

  abstract protected function handler();

  public function process() {
    try {
      $this->handler();
    } catch (\Exception $e) {
      $this->event_->handlerError();
      return;
    }
    $this->event_->handlerOver();
  }

  public function getEvent():Event {
    return $this->event_;
  }

  private $event_;
}
