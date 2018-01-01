<?php


class Config {

/**
 * 每一个配置项都是以 'const ' 开头， ';' 结束
 *
 * 比如 const sample=1;
 *
 * 注释以  '//'  开头
 *
 */
// add config after this line


  const MongoDB_default_addr='';
  const MongoDB_default_dbname='';
  const MongoDB_default_user="";
  const MongoDB_default_passwd="";

  // TimerEvent 存储的集合名
  const Timer_collection_name="timer";
  // 动态Event 存储的集合名
  const Event_collection_name="event";



// ---------------  Logger --------------//

  const Logger_level =  \Tiny\Logger::INFO;  // Logger::INFO
  const Logger_path = "";

  // 如果使用 tiny提供的Log4php logger，需要配置以下项
  //Log4php Logger类文件位置，要确定require_once能成功
  // 如果不使用log4php 可以不配置此项
  const Logger_log4php_class_file = "";


// add config before this line


}

