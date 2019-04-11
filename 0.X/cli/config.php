<?php


namespace Config;

/**
 * 每一个配置项都是以 'const ' 开头， ';' 结束
 *
 * 比如 const sample=1;
 *
 * 注释以  '//'  开头
 *
 */


class MongoDB {
  const default_addr='';
  const default_dbname='';
  const default_user="";
  const default_passwd="";

  // TimerEvent 存储的集合名
  const Timer_collection_name="timer";
  // 动态Event 存储的集合名
  const Event_collection_name="event";

}
