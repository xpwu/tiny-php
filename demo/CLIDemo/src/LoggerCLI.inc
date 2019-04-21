<?php


namespace Demo\CLI;


use Tiny\CLI;
use Tiny\Core\Utils;
use Tiny\Logger;

class LoggerCLI extends CLI {

  /**
   * @param array $argv . argv[0] -> first argv, not cli name
   */
  protected function run(array $argv): void {
    Logger::getInstance()->info(Utils::stringArray2string($argv));
    Logger::getInstance()->warn(Utils::stringArray2string($argv));
    Logger::getInstance()->error(Utils::stringArray2string($argv));
  }

  /**
   * php cli.phar <cmd> -h 的返回
   * @return string
   */
  function getHelp(): string {
    return "回显输入的参数";
  }

  /**
   * php cli.phar -l 时，此CLI 显示的帮助信息
   * @return string
   */
  function listInfo(): string {
    return "验证logger的cli";
  }
}