<?php


namespace Tiny\CLI;


use Tiny\CLI;
use Tiny\DB\Index\Annotation\AllNeedCreateIndex;
use Tiny\DB\Index\Annotation\NeedCreateIndex;
use Tiny\Logger;

class CreateIndex extends CLI {

  /**
   * @param array $argv . argv[0] -> first argv
   * @throws \Exception
   */
  protected function run(array $argv): void {
    if (count($argv) != 1) {
      Logger::getInstance()->error("argv error! please use -h");
      return;
    }

    if ($argv[0] == "-l") {
      $helper = AllNeedCreateIndex::getImpl();
      /**
       * @var NeedCreateIndex[]
       */
      $all = $helper->getAll();
      echo "sum = " . count($all) . PHP_EOL;
      echo "taskName ---> description" .PHP_EOL;
      echo "---------------" . PHP_EOL;

      foreach ($all as $needCreateIndex) {
        echo  get_class($needCreateIndex) . " ---> "
          . $needCreateIndex::description() . PHP_EOL;
      }

      return;
    }

    if ($argv[0] == "-a") {
      $helper = AllNeedCreateIndex::getImpl();
      /**
       * @var NeedCreateIndex[]
       */
      $all = $helper->getAll();

      foreach ($all as $needCreateIndex) {
        Logger::getInstance()->info(
          "create index: " . get_class($needCreateIndex) . " ---> "
          . $needCreateIndex::description() . " ...");

        try {
          $needCreateIndex::createIndex();
        } catch (\Exception $exception) {
          Logger::getInstance()->fatal("create index error: "
            . get_class($needCreateIndex), $exception);
        }

      }

      Logger::getInstance()->info("CreateIndex over!");

      return;
    }

    /**
     * @var NeedCreateIndex $task
     */
    $task = $argv[0];
    if (!class_exists($task)
      || !is_subclass_of($task, NeedCreateIndex::class)) {
      Logger::getInstance()->error("$task is not a valid task, please use -l");
      return;
    }

    try {
      $task::createIndex();
    } catch (\Exception $exception) {
      Logger::getInstance()->fatal("create index error: "
        . get_class($task), $exception);
    }

    Logger::getInstance()->info("CreateIndex over!");
  }

  /**
   * php cli.phar <cmd> -h 的返回
   * @return string
   */
  function getHelp(): string {
    $help = <<<EOF
<taskName>
  -l: 所有需要创建索引的任务列表，展示为： taskName ---> description
  -a: 执行所有需要创建索引的任务
EOF;

    return $help;
  }


  /**
   * php cli.phar -l 时，此CLI 显示的帮助信息
   * @return string
   */
  function listInfo(): string {
    return "创建数据库索引";
  }
}