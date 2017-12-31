<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/3/9
 * Time: 上午11:52
 */

namespace CLI;


abstract class CLI {
  static public function name():string {
    return get_class();
  }

  /**
   * @param array $argv. argv[0] -> first argv
   */
  abstract function process(array $argv):void;

  /**
   * php cli.phar <cmd> -h 的返回
   * @return string
   */
  abstract function getHelp():string ;

  /**
   * php cli.phar -l 时，此CLI 显示的帮助信息
   * @return string
   */
  abstract function listInfo():string ;

}