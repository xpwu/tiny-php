<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/31
 * Time: 下午9:38
 */

namespace Tiny\CLI;


use Tiny\Logger;

class StdLogger extends Logger {

  // 颜色
  private const NONE = "\e[0m";
  private const BLACK = "\e[0;30m";
  private const L_BLACK = "\e[1;30m";
  private const RED = "\e[0;31m";
  private const L_RED = "\e[1;31m";
  private const GREEN = "\e[0;32m";
  private const L_GREEN = "\e[1;32m";
  private const BROWN = "\e[0;33m";
  private const YELLOW = "\e[1;33m";
  private const BLUE = "\e[0;34m";
  private const L_BLUE = "\e[1;34m";
  private const PURPLE = "\e[0;35m";
  private const L_PURPLE = "\e[1;35m";
  private const CYAN = "\e[0;36m";
  private const L_CYAN = "\e[1;36m";
  private const GRAY = "\e[0;37m";
  private const WHITE = "\e[1;37m";

  // 字体
  private const BOLD = "\e[1m";
  private const UNDERLINE = "\e[4m";
  private const BLINK = "\e[5m";
  private const REVERSE = "\e[7m";
  private const HIDE = "\e[8m";
  private const CLEAR = "\e[2J";
  private const CLRLINE = "\r\e[K\" //or \"\e[1K\r";

  private const levelMap = [
      "  ALL"
    , "TRACE"
    , "DEBUG"
    , " INFO"
    , " WARN"
    , "ERROR"
    , "FATAL"
    , "  OFF"
  ];

  public function init() {

  }

  public function trace(string $message, ?\Throwable $throwable = null) {
    $this->format(Logger::TRACE, $message, $throwable);
  }

  public function debug(string $message, ?\Throwable $throwable = null) {
    $this->format(Logger::DEBUG, $message, $throwable);
  }

  public function info(string $message, ?\Throwable $throwable = null) {
    $this->format(Logger::INFO, $message, $throwable);
  }

  public function warn(string $message, ?\Throwable $throwable = null) {
    $this->format(Logger::WARN
      , $message, $throwable, self::YELLOW);
  }

  public function error(string $message, ?\Throwable $throwable = null) {
    $this->format(Logger::ERROR
      , $message, $throwable, self::RED);
  }

  public function fatal(string $message, ?\Throwable $throwable = null) {
    $this->format(Logger::FATAL
      , $message, $throwable, self::RED);

    // fatal, stop
    throw new NormalError("fatal error, exit");
  }

//  private function format(int $needLevel, string $type
//    , string $message, \Throwable $throwable=null) {
//    if ($needLevel < $this->level->value()) {
//      return;
//    }
//
//    $this->getLocationInformation();
//
//    $throwa = ($throwable == null)?"":("\n".$throwable);
//    file_put_contents('php://output'
//      , $this->getDate()."[$type]".$this->fullInfo."---".$message
//      . " " . $throwa. PHP_EOL);
//  }

  private function format(int $needLevel, string $message
    , ?\Throwable $throwable=null, ?string $color = null) {

    if ($needLevel < $this->level->value()) {
      return;
    }

    $this->getLocationInformation();

    $throwa = ($throwable == null)?"":($throwable . PHP_EOL);

    $beginColor = $color;
    $endColor = self::NONE;
    if ($color === null) {
      $beginColor = "";
      $endColor = "";
    }

    file_put_contents('php://output'
      , $beginColor . $this->getDate()
      . "[" . self::levelMap[$needLevel] ."] "
      . $this->fullInfo."---" . $message . PHP_EOL
      . $throwa. $endColor);
  }
}