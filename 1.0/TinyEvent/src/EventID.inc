<?php


namespace Tiny\Event;


class EventID {
  public function __construct(string $id) {
    $this->id_ = $id;
  }

  public function __toString():string {
    return $this->id_;
  }

  private $id_;
}