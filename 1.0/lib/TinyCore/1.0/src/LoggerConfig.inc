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

/**
 *
 * Logger的相关配置
 */
interface LoggerConfig extends Annotation\OperationConfig {

  /**
   * 下面是所有level的取值，按照顺序级别递增。此常量不需要修改
   */
  const AllLevelValue = [
    All::class,
    Trace::class,
    Debug::class,
    Info::class,
    Warn::class,
    Error::class,
    Fatal::class,
    Off::class,
  ];

  /**
   * 配置Logger的级别，可配置的值为allValue中所列
   */
  const level = Info::class;
}