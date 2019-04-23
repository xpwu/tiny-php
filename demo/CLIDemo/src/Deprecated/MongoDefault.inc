<?php


namespace Demo\CLI\Deprecated;


use Tiny\CLI;
use Tiny\Deprecated\Logic\MongodbDefaultConfig;
use Tiny\Logger;

class MongoDefault extends CLI {

  /**
   * @param array $argv . argv[0] -> first argv, not cli name
   */
  protected function run(array $argv): void {
    Logger::getInstance()->info(
      "[" . MongodbDefaultConfig::default_user
      . "@" . MongodbDefaultConfig::default_passwd . "]"
      . MongodbDefaultConfig::default_addr
      . '/' . MongodbDefaultConfig::default_dbname);
  }

  /**
   * php cli.phar <cmd> -h 的返回
   * @return string
   */
  function getHelp(): string {
    return "";
  }

  /**
   * php cli.phar -l 时，此CLI 显示的帮助信息
   * @return string
   */
  function listInfo(): string {
    return "default db demo";
  }
}