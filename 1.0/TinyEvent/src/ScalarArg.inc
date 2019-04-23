<?php


namespace Tiny\Event;


class ScalarArg implements EventArg {
  private function __construct(string $value) {
    $this->value_ = $value;
  }

  static public function int(int $value):EventArg {
    return new ScalarArg((string)$value);
  }

  static public function float(float $value):EventArg {
    return new ScalarArg((string)$value);
  }

  static public function string(string $value):EventArg {
    return new ScalarArg($value);
  }

  static public function bool(bool $value):EventArg {
    return new ScalarArg((string)$value);
  }

  public function __toString():string {
    return $this->value_;
  }

  private $value_;
}