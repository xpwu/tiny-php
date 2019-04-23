<?php


namespace Demo\CLI\DBIndex;


use Tiny\DB\Index\Annotation\NeedCreateIndex;
use Tiny\Logger;

class Collection implements NeedCreateIndex {

  static function createIndex(): void {
    Logger::getInstance()->info("create over");
  }

  static function description(): string {
    return "create index demo";
  }
}