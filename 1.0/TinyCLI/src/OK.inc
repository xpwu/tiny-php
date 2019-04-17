<?php


namespace Tiny\CLI;



class OK extends \Error {
  public function __construct() {
    parent::__construct();
  }
}