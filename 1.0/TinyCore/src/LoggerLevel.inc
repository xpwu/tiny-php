<?php


namespace Tiny\Core;


class LoggerLevel {
  public function __construct(int $level) {
    $this->level_ = $level;
  }

  public function value():int {
    return $this->level_;
  }

  private $level_;
}