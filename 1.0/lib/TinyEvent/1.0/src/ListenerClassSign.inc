<?php


namespace Tiny\Event;


class ListenerClassSign {
  public function __construct(string $classSign) {
    $this->classSign_ = $classSign;
  }

  public function __toString():string {
    return $this->classSign_;
  }

  private $classSign_;
}