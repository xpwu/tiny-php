<?php


namespace Tiny\Core;


interface LoggerConfig extends Annotation\Config {
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
  const level = "Info";
}