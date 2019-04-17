<?php


namespace Tiny\CLI;



class NormalError extends \Error {
  public function __construct(string $message) {
    parent::__construct($message);
  }

  public function __toString() {
    return "Error: " . $this->getMessage() . PHP_EOL;
  }
}