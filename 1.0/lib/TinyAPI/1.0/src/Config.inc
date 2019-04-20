<?php


namespace Tiny\API;


use Tiny\Core\Annotation\OperationConfig;
use Tiny\Log4PHPAdapter;

/**
 *
 * TinyAPI 的配置
 */
interface Config extends OperationConfig {
  /**
   * 配置项目使用的Logger库，默认使用Log4PHP
   *
   * 如果需要配置为其他Logger，请填写类的包括命名空间的名字
   * 配置的Logger必须是 Tiny\Logger 的子类
   */
  const logger = Log4PHPAdapter::class;
}