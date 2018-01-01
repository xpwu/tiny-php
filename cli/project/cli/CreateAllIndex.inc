<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2018/1/2
 * Time: 上午2:17
 */

namespace CLI;


use Tiny\Phpinte;

class CreateAllIndex extends \Tiny\CLI {

  /**
   * @param array $argv . argv[0] -> first argv
   */
  function process(array $argv): void {
    /**
     * @var $class \Tiny\DB\CreateIndexInterface
     */
    foreach (Phpinte::getAllClass() as $class) {
      try {
        if (is_subclass_of($class, "Tiny\DB\CreateIndexInterface")) {
          \Tiny\Logger::getInstance()->info("create index: ".$class);
          $class::createIndex();
        }
      } catch (\Exception $exception){}
    }
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
    return "创建所有数据库的索引";
  }
}