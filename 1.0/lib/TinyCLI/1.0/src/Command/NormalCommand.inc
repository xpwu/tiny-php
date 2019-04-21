<?php


namespace Tiny\CLI\Command;


use Inte\RunTime;
use Tiny\CLI;
use Tiny\CLI\Command;

class NormalCommand implements Command {

  public function __construct(array $argv, bool $force = false) {
//    $cmdName = explode('/', $argv[0]);
//    $cmdName = implode('\\', $cmdName);
//    $clsname = "CLI\\".$cmdName;
    $cmdName = $argv[0];
    $clsname = $cmdName;

    if (!class_exists($clsname)) {
      throw new CLI\NormalError("not find command --- ".$cmdName);
    }

    $this->cli_ = new $clsname();
    $this->argv_ = array_slice($argv, 1);
    $this->force_ = $force;

    if (count($this->argv_) >= 1 && $this->argv_[0] == '-h') {
      echo "usage: php "
        . RunTime::default()->getPharBaseName()
        . " ".$cmdName." ".$this->cli_->getHelp().PHP_EOL;

      throw new CLI\OK();
    }
  }

  function run() {
    if (!$this->force_) {
      $rand = rand(1000, 9999);
      fwrite(STDOUT, "Enter $rand: ");
      $input = trim(fgets(STDIN));
      if ($rand != $input) {
        throw new CLI\NormalError("input Error!!!");
      }
    }

    $this->cli_->process($this->argv_);

  }

  /**
   *@var CLI
   */
  private $cli_;
  private $argv_;
  private $force_ = false;
}