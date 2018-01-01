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


  const Timer_collection_name="timer";
  const Event_collection_name="event";



// ---------------  Logger --------------//

  const Logger_level = 2;  // Logger::INFO
  const Logger_path = "";

  //Log4php Logger类文件位置，要确定require_once能成功
  const Logger_log4php_class_file = "";


// add config before this line


}

