<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2018/1/2
 * Time: 上午2:17
 */

namespace CLI;


use Tiny\CLI;
use Tiny\Deprecated\Annotation\CreateAllIndexHelper;
use Tiny\Logger;

/**
 * Class CreateAllIndex
 * @deprecated
 */
class CreateAllIndex extends CLI {

  /**
   * @param array $argv . argv[0] -> first argv
   * @throws \Exception
   */
  protected function run(array $argv): void {

    $helper = CreateAllIndexHelper::getImpl();

    /**
     * @var $class \Tiny\DB\CreateIndexInterface
     */
    foreach ($helper->getAll() as $class) {
      try {
        Logger::getInstance()->info("create index: ".$class);
        $class::createIndex();
      } catch (\Exception $exception){
        Logger::getInstance()->error("create index error: ".$class, $exception);
      }
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
    return "创建所有数据库的索引，此命令即将废弃，请尽快替换为新的代码";
  }
}