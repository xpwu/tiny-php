<?php

/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/30
 * Time: 上午1:06
 */
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


  const Logger_class_name = "Base\\Log4php"; // 包括命名空间
  const Logger_level = 2;  // Logger::INFO
  const Logger_path = "";
  


// add config before this line


}

