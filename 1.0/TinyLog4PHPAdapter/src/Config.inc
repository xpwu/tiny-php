<?php


namespace Tiny\Log4PHPAdapter;


use Tiny\Log4PHPAdapter;

class Config implements \Tiny\Annotation\Config {
  function getHelp(): string {
    return "level: int 配置输出的log级别";
  }

  const level = Log4PHPAdapter::INFO;
}
