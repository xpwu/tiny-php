<?php


namespace Tiny\Event\Center;


class Name {

  private function __construct(string $name) {
    $this->name_ = $name;
  }

  static public function to():Name {
    return new Name(static::class);
  }

  public function __toString():string {
    return $this->name_;
  }

  private $name_;
}