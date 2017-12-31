<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2018/1/1
 * Time: 上午3:08
 */

namespace CLI;


use Base\Logger;

class Demo extends CLI {

  /**
   * @param array $argv . argv[0] -> first argv
   */
  function process(array $argv): void {
    // TODO: Implement process() method.
    Logger::getInstance()->info($argv[0]);
    throw new \Exception("test execption");
  }

  /**
   * php cli.phar <cmd> -h 的返回
   * @return string
   */
  function getHelp(): string {
    return "any";
  }

  /**
   * php cli.phar -l 时，此CLI 显示的帮助信息
   * @return string
   */
  function listInfo(): string {
    return "this is demo";
  }
}