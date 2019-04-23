<?php

// ------ Operation Config ------

namespace Tiny\Core {
      
	/**
	 *
	 * Logger的相关配置
	 */
	interface LoggerConfig {
	    
	  /**
	   * 下面是所有level的取值，按照顺序级别递增。此常量不需要修改
	   */
	  public const AllLevelValue = [
			'Tiny\Core\LoggerLevel\All',
			'Tiny\Core\LoggerLevel\Trace',
			'Tiny\Core\LoggerLevel\Debug',
			'Tiny\Core\LoggerLevel\Info',
			'Tiny\Core\LoggerLevel\Warn',
			'Tiny\Core\LoggerLevel\Error',
			'Tiny\Core\LoggerLevel\Fatal',
			'Tiny\Core\LoggerLevel\Off',
			];
	        
	  /**
	   * 配置Logger的级别，可配置的值为allValue中所列
	   */
	  public const level = 'Tiny\Core\LoggerLevel\Info';
	          
	}      
}


namespace Tiny\API {
      
	/**
	 *
	 * TinyAPI 的配置
	 */
	interface Config {
	    
	  /**
	   * 配置项目使用的Logger库，默认使用Log4PHP
	   *
	   * 如果需要配置为其他Logger，请填写类的包括命名空间的名字
	   * 配置的Logger必须是 Tiny\Logger 的子类
	   */
	  public const logger = 'Tiny\Log4PHPAdapter';
	          
	}      
}


namespace Tiny\Deprecated\Logic {
      
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
	interface MongodbDefaultConfig {
	    
	  /** 老版本配置的默认的数据库地址 */
	  public const default_addr = '';
	        
	  /** 老版本配置的默认的数据库名 */
	  public const default_dbname = '';
	        
	  /** 老版本默认数据库的用户名 */
	  public const default_user = '';
	        
	  /** 老版本默认数据库的密码 */
	  public const default_passwd = '';
	          
	}      
}

