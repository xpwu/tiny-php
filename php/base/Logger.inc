<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/31
 * Time: 上午1:59
 */

namespace Base;


abstract class Logger {
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

  abstract public function init();

  abstract public function trace($message, $throwable = null);
  abstract public function debug($message, $throwable = null);
  abstract public function info($message, $throwable = null);
  abstract public function warn($message, $throwable = null);
  abstract public function error($message, $throwable = null);
  abstract public function fatal($message, $throwable = null);

  protected $request;
}
