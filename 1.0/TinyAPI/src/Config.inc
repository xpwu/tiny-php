<?php


namespace Tiny\API;


use Tiny\Core\Annotation\OperationConfig;
use Tiny\Core\LogConfigGroup;
use Tiny\Log4PHPAdapter;


interface Config extends OperationConfig, LogConfigGroup {
  /**
   * 配置项目使用的Logger库，默认使用Log4PHP
   * 使用该库，需要在项目中加入 TinyLog4PHPAdapter 依赖
   *
   * 如果需要配置为其他Logger，请填写类的包括命名空间的名字
   * 配置的Logger必须是 Tiny\Logger 的子类
   */
  const logger = Log4PHPAdapter::class;
}