<?php


namespace Tiny\CLI;



class NormalError extends \Error {
  public function __construct(string $message) {
    parent::__construct($message);
  }

  public function __toString() {
    if ($this->getMessage() === "") {
      return "";
    }

    return "Error: " . $this->getMessage() . PHP_EOL;
  }
}