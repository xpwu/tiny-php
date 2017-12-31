<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/31
 * Time: 上午1:59
 */

namespace Base;


//use Throwable;

abstract class Logger {
  const ALL = 0;
  const TRACE = 1;
  const DEBUG = 2;
  const INFO = 3;
  const WARN = 4;
  const ERROR = 5;
  const FATAL = 6;
  const OFF = 7;

  /**
   * @var Logger
   */
  static private $instance = null;

  static public function getInstance() {
    if (self::$instance == null) {
      $className = \Config::Logger_class_name;
      self::$instance = new $className();
      self::$instance->init();
    }
    return self::$instance;
  }

  function __clone() {
    return $this;
  }

  public function setRequest(Request $request) {
    $this->request = $request;
  }

  abstract protected function init();

  abstract public function trace(string $message, \Throwable $throwable = null);
  abstract public function debug(string $message, \Throwable $throwable = null);
  abstract public function info(string $message, \Throwable $throwable = null);
  abstract public function warn(string $message, \Throwable $throwable = null);
  abstract public function error(string $message, \Throwable $throwable = null);
  abstract public function fatal(string $message, \Throwable $throwable = null);

  /**
   * @var Request
   */
  protected $request = null;
}
