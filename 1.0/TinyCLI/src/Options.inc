<?php


namespace Tiny\CLI;


use Inte\RunTimeEnv;

class Options {

  public function __construct() {
    $this->configFile = RunTimeEnv::getInstance()->getRunTime()->getPharDir()
      . DIRECTORY_SEPARATOR . "config.php";
  }

  /**
   * @throws OK
   */
  public function parse():void {
    $argv = $_SERVER['argv'];
    $this->cliName_ = $argv[0];

    if (count($argv) == 1) {
      $this->echoUsage();
      throw new OK();
    }

    $length = count($argv);

    $i = 1;
    for (; $i < $length; ++$i) {

      if ($argv[$i] == '-h') {
        $this->echoUsage();
        throw new OK();
      }
      if ($argv[$i] == '-l') {
        self::list();
        return false;
      }
      if ($argv[$i] == '-f') {
        $this->force = true;
        continue;
      }
      if ($argv[$i] == '-c' && $i+1 < $length) {
        $this->configFile = $argv[++$i];
        continue;
      }

      // else maybe command
      break;
    }

    $this->commandArgv_ = array_slice($argv, $i);
  }

  private function echoUsage():void {
    $usage = <<<EOF
usage: php $this->cliName_ [-c <filename>, -f, -l, -h] <command> args
      -h: show this message;
      -l: list all commands;
      -f <command>: force exec <command>;
      <command> -h: show command help;
      -c <filename>: config filename, default is './config.php'.

EOF;

    echo $usage;
  }

  /**
   * @var string[]
   */
  private $commandArgv_;
  private $cliName_;

  public $force = false;
  public $configFile = "./config.php";
}