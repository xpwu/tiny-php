<?php


namespace Demo\CLI\Event;


class Event extends \Tiny\Event\Event {
  public function __construct(int $arg1, int $arg2) {
    $this->arg1_ = $arg1;
    $this->arg2_ = $arg2;

    parent::__construct($arg1);
  }

  public function getArg1():int {
    return $this->arg1_;
  }

  public function getArg2():int {
    return $this->arg2_;
  }

  private $arg1_;
  private $arg2_;
}