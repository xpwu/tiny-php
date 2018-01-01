<?php
use Tiny\Logger;

/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/3/9
 * Time: 上午11:48
 */

class Option {
  public $force;
  public $configFile="./Config.php";
}


class Index {
  static private function tips(string $msg) {
    echo $msg;
  }

  static private function helpInfo($argv) {
    $tip=<<<EOF
usage: php ".$argv[0]. " [-c <filename>, -f, -l, -h] <command> args"
      -h: show this message;
      -l: list all commands;
      -f <command>: force exec <command>;
      <command> -h: show command help;
      -c <filename>: Config filename, default is './Config.php'.

EOF;

    echo $tip;
  }

  static private function list() {
    // phpinte 集成工具生成的中间文件
    foreach (inte_AutoLoader::$classMap_ as $class => $file) {
      try {
        if (is_subclass_of($class, \Tiny\CLI::name())) {
          /**
           * @var \Tiny\CLI $cli
           */
          $cli = new $class();
          $clsName = get_class($cli);
          //trim CLI\
          $clsName = substr($clsName, 4);
          self::tips($clsName."\t".$cli->listInfo().PHP_EOL);
        }
      } catch (Exception $exception){}
    }
  }

  static private function parseOption(array& $argv, Option $option):bool {
    if (count($argv) == 1) {
      self::helpInfo($argv);
      return false;
    }

    $length = count($argv);

    $i = 1;
    for (; $i < $length; ++$i) {

      if ($argv[$i] == '-h') {
        self::helpInfo($argv);
        return false;
      }
      if ($argv[$i] == '-l') {
        self::list();
        return false;
      }
      if ($argv[$i] == '-f') {
        $option->force = true;
        continue;
      }
      if ($argv[$i] == '-c' && $i+1 < $length) {
        $option->configFile = $argv[++$i];
        continue;
      }

      // else maybe command
      break;
    }

    $argv = array_slice($argv, $i);

    return true;
  }

  static public function main() {

    date_default_timezone_set('PRC'); // 设置时区

    function exception_error_handler($errno, $errstr, $errfile, $errline ) {
       throw new ErrorException($errstr, 0, $errno, $errfile, $errline);
    }
    set_error_handler("exception_error_handler");

    $argv = $_SERVER['argv'];
    $option = new Option();
    $phar = $argv[0];

    if (!self::parseOption($argv, $option)) {
      return;
    }

    $cmdName = $argv[0];
    $clsname = "CLI\\".$cmdName;

    if (!class_exists($clsname)) {
      self::tips("not find command --- ".$cmdName);
      return;
    }

    $v = array_slice($argv, 1);

    /**
     * @var \Tiny\CLI $cmd
     */
    $cmd = new $clsname();
    if (count($v) >= 1 && $v[0] == '-h') {
      echo "usage: php ".$phar." ".$cmdName." ".$cmd->getHelp().PHP_EOL;
      return;
    }

    if (!$option->force) {
      $rand = rand(1000, 9999);
      fwrite(STDOUT, "Enter $rand: ");
      $input = trim(fgets(STDIN));
      if ($rand != $input) {
        fwrite(STDERR, "input Error!!!\n");
        return;
      }
    }

    if (substr($option->configFile, 0, 1) != '/') {
      $option->configFile = dirname(substr(__DIR__, 7))
        ."/".$option->configFile;
    }
    if (!file_exists($option->configFile)) {
      echo "not find config file ---".$option->configFile.PHP_EOL;
      return;
    }

    require_once ($option->configFile);

    // ------ project init ------
    ProjectInit::init();

    // -------init logger -----
    Logger::setConcreteLogger(new \Tiny\StdLogger());

    try {
      $cmd->process($v);
    } catch (Exception $e) {
      Logger::getInstance()->fatal("CLI run error", $e);
    }
  }
}

Index::main();
