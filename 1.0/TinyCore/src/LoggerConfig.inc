<?php


namespace Tiny\Core;


use Tiny\Core\LoggerLevel\All;
use Tiny\Core\LoggerLevel\Debug;
use Tiny\Core\LoggerLevel\Error;
use Tiny\Core\LoggerLevel\Fatal;
use Tiny\Core\LoggerLevel\Info;
use Tiny\Core\LoggerLevel\Off;
use Tiny\Core\LoggerLevel\Trace;
use Tiny\Core\LoggerLevel\Warn;

interface LoggerConfig extends Annotation\Config {
  /**
   * 下面是所有level的取值
   */

  const all = All::class;
  const trace = Trace::class;
  const debug = Debug::class;
  const info = Info::class;
  const warn = Warn::class;
  const error = Error::class;
  const fatal = Fatal::class;
  const off = Off::class;

  /**
   * 配置LoggerLevel 可取值按照如下，逐级递增，默认为 "Info"
   *
   *  "All"
   *  "Trace"
   *  "Debug"
   *  "Info"
   *  "Warn"
   *  "Error"
   *  "Fatal"
   *  "Off"
   */

  /**
   * 配置LoggerLevel，取值为此类中列出的其他常量, 按照如下的顺序逐级递增
   *
   * self::all
   * self::trace
   * self::debug
   * self::info
   * self::warn
   * self::error
   * self::fatal
   * self::off
   *
   */
  const level = self::info;
}