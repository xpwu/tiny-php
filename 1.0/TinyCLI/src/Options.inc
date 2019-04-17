<?php


namespace Tiny\CLI;


use Inte\RunTimeEnv;
use Tiny\CLI\Command\ListCommand;
use Tiny\CLI\Command\NormalCommand;

class Options {

  /**
   * Options constructor.
   * @throws OK
   */
  public function __construct() {
    $this->configFile = RunTimeEnv::getInstance()->getRunTime()->getPharDir()
      . DIRECTORY_SEPARATOR . "config.php";

    $this->parse();
  }

  private function parse():void {
    $argv = $_SERVER['argv'];
    $this->cliName_ = $argv[0];

    if (count($argv) == 1) {
      $this->echoUsage();
      throw new OK();
    }

    $length = count($argv);

    $force = false;

    $i = 1;
    for (; $i < $length; ++$i) {

      if ($argv[$i] == '-h') {
        $this->echoUsage();
        throw new OK();
      }
      if ($argv[$i] == '-l') {
        $this->command_ = new ListCommand();
        break;
      }
      if ($argv[$i] == '-f') {
        $force = true;
        continue;
      }
      if ($argv[$i] == '-c' && $i+1 < $length) {
        $configFile = $argv[++$i];
        if (substr($configFile, 0, 1) != '/') {
          $configFile = RunTimeEnv::getInstance()->getRunTime()->getPharDir()
            . DIRECTORY_SEPARATOR . $configFile;
        }
        if (!file_exists($configFile)) {
          throw new NormalError("can Not find config file ---".$configFile);
        }

        require_once ($configFile);

        continue;
      }

      // else maybe command
      break;
    }

    $argv = array_slice($argv, $i);
    if (count($argv) == 0) {
      throw new NormalError("argv error! Please use -h");
    }

    $this->command_ = new NormalCommand($argv, $force);
  }

  private function echoUsage():void {
    $usage = <<<EOF
usage: php $this->cliName_ [-c <filename>, -f, -l, -h] <command> args
      -h: show this message;
      -l: list all commands;
      -f <command>: force exec <command>;
      <command> -h: show command help;
      -c <filename>: config filename, default is './config.php' 
          and the dir is same to the dir of xxx.phar.

EOF;

    echo $usage;
  }

  public function getCommand():Command {
    return $this->command_;
  }


  private $cliName_;

  public $configFile_ = "./config.php";

  /**
   * @var Command
   */
  private $command_;
}