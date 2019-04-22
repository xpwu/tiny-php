<?php


namespace Demo\CLI\Event;


use Tiny\Logger;

class Listener extends \Tiny\Event\Listener {

  public function __construct(Event $event) {
    parent::__construct($event);

    $this->event_ = $event;
  }

  protected function handler() {
    Logger::getInstance()->info("arg1 ".$this->event_->getArg1());
    Logger::getInstance()->info("arg2 ".$this->event_->getArg2());
  }

  private $event_;
}