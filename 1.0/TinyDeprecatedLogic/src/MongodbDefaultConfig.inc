<?php


namespace Tiny\Deprecated\Logic;


use Tiny\Core\Annotation\OperationConfig;

/**
 *
 * 如果看到此配置项说明代码中仍有未替换完的代码
 * 如下的配置主要是为了兼容老版本的一下配置项
 * 按照之前的配置即可，如果服务发生了变动，则需要按照
 * 新的服务来
 *
 * class MongoDB {
 * const default_addr='';
 * const default_dbname='';
 * const default_user="";
 * const default_passwd="";
 * }
 *
 */
interface MongodbDefaultConfig extends OperationConfig {
  /** 老版本配置的默认的数据库地址 */
  const default_addr = '';
  /** 老版本配置的默认的数据库名 */
  const default_dbname = '';
  /** 老版本默认数据库的用户名 */
  const default_user = "";
  /** 老版本默认数据库的密码 */
  const default_passwd = "";
}