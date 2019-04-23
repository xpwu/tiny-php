<?php


namespace Demo\CLI\Deprecated;


use Tiny\DB\CreateIndexInterface;
use Tiny\Logger;

class DBIndex implements CreateIndexInterface {

  static public function createIndex() {
    Logger::getInstance()->info("Demo\CLI\Deprecated\DBIndex over");
  }
}