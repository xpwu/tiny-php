<?php


namespace Tiny\Core\LoggerLevel;


use Tiny\Core\LoggerLevel;
use Tiny\Logger;

class Trace extends LoggerLevel {
  public function __construct() {
    parent::__construct(Logger::TRACE);
  }
}