<?php


namespace Demo\CLI;


use Demo\CLI\Event\Event;
use Demo\CLI\Event\Named;
use Tiny\CLI;
use Tiny\Event\EventCenter;
use Tiny\Logger;

class NamedECCLI extends CLI {

  /**
   * @param array $argv . argv[0] -> first argv, not cli name
   */
  protected function run(array $argv): void {
    if (count($argv) === 0) {
      Logger::getInstance()->fatal("参数错误，请-h查看");
    }

    EventCenter::byName(Named::toName())->postEvent(new Event((int)$argv[0], "named"));
  }

  /**
   * php cli.phar <cmd> -h 的返回
   * @return string
   */
  function getHelp(): string {
    return "输入一个整数 其中有监听10与5参数的监听者";
  }

  /**
   * php cli.phar -l 时，此CLI 显示的帮助信息
   * @return string
   */
  function listInfo(): string {
    return "验证named EventCenter";
  }
}