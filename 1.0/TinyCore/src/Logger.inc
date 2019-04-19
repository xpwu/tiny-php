<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/31
 * Time: 上午1:59
 */

namespace Tiny;


use Tiny\Core\LoggerConfig;
use Tiny\Core\LoggerLevel;
use Tiny\Core\Time;

abstract class Logger {

  public const ALL = 0;
  public const TRACE = 1;
  public const DEBUG = 2;
  public const INFO = 3;
  public const WARN = 4;
  public const ERROR = 5;
  public const FATAL = 6;
  public const OFF = 7;

  static public function setConcreteLogger(Logger $logger) {
    self::$instance = $logger;
  }
  static public function hasSetConcreteLogger():bool {
    return self::$instance !== null;
  }
  /**
   * @var Logger
   */
  static private $instance = null;

  static private $isInited = false;

  static public function getInstance():Logger {
    if (self::$instance === null) {
      throw new \Error("Not set Logger!!!");
    }

    if (!self::$isInited) {
      self::$instance->init();
      self::$isInited = true;
    }
    return self::$instance;
  }

  function __clone() {
    return $this;
  }

  public function __construct() {
    $level = "Tiny\\Core\\LoggerLevel\\" . LoggerConfig::level;
    $this->level = new $level();
  }

  public function setRequest(Request $request) {
    $this->request = $request;
  }

  abstract protected function init();

  abstract public function trace(string $message, ?\Throwable $throwable = null);
  abstract public function debug(string $message, ?\Throwable $throwable = null);
  abstract public function info(string $message, ?\Throwable $throwable = null);
  abstract public function warn(string $message, ?\Throwable $throwable = null);
  abstract public function error(string $message, ?\Throwable $throwable = null);
  abstract public function fatal(string $message, ?\Throwable $throwable = null);

  protected function getLocationInformation() {

    $trace = debug_backtrace();
    $prevHop = null;
    // make a down search to identify the caller
    $hop = array_pop($trace);
    while($hop !== null) {
      if(isset($hop['class'])) {
        // we are sometimes in functions = no class available: avoid php warning here
        $className = $hop['class'];
        if(!empty($className) && ($className == get_class() ||
            is_subclass_of($className, get_class()) )) {
          $this->line = $hop['line'];
          $this->fileName = $hop['file'];
          break;
        }
      }
      $prevHop = $hop;
      $hop = array_pop($trace);
    }
    $this->className = isset($prevHop['class']) ? $prevHop['class'] : 'main';
    if(isset($prevHop['function']) and
      $prevHop['function'] !== 'include' and
      $prevHop['function'] !== 'include_once' and
      $prevHop['function'] !== 'require' and
      $prevHop['function'] !== 'require_once') {

      $this->methodName = $prevHop['function'];
    } else {
      $this->methodName = 'main';
    }

    $this->fullInfo = $this->className . '.' . $this->methodName .
      '(...' . substr($this->fileName, -25) . ':' . $this->line . ')';
  }

  protected function getDate():string {
    return Time::getCurrentMillSecondToString();
  }

  /**
   * @var LoggerLevel
   */
  protected $level;

  /**
   * @var Request
   */
  protected $request = null;

  protected $line = null;
  protected $fileName = null;
  protected $methodName = null;
  protected $className = null;
  protected $fullInfo = null;
}
