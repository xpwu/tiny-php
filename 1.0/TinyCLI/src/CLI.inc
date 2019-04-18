<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/3/9
 * Time: 上午11:52
 */

declare(strict_types=1);

namespace Tiny;



abstract class CLI implements CLIAnnotation {
  /**
   * @return string
   * @deprecated
   */
  static public function name():string {
    return get_class();
  }

  /**
   * @param array $argv. argv[0] -> first argv
   */
  abstract protected function run(array $argv):void;

  /**
   * @param array $argv. argv[0] -> first argv
   */
  public function process(array $argv):void {
    $this->run($argv);
  }

  /**
   * php cli.phar <cmd> -h 的返回
   * @return string
   */
  abstract function getHelp():string ;

//  /**
//   * php cli.phar -l 时，此CLI 显示的帮助信息
//   * @return string
//   */
//  abstract function listInfo():string ;

}