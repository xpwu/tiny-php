<?php


namespace Demo\CLI\Event;


use Tiny\Event\ScalarArg;

class Event extends \Tiny\Event\Event {
  public function __construct(int $arg1, string $arg2) {
    $this->arg1_ = $arg1;
    $this->arg2_ = $arg2;

    parent::__construct(ScalarArg::int($arg1));
  }

  public function getArg1():int {
    return $this->arg1_;
  }

  public function getArg2():string {
    return $this->arg2_;
  }

  private $arg1_;
  private $arg2_;
}