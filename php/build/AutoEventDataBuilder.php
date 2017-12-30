<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/30
 * Time: 下午11:11
 */

set_include_path(dirname(__FILE__)."/"
  . PATH_SEPARATOR . get_include_path());

require_once("AutoLoader.inc");

//set_include_path(dirname(__FILE__)."/../"
//  . PATH_SEPARATOR . get_include_path());

inte_AutoLoader::$prefixDir = dirname(__FILE__)."/..";
inte_AutoLoader::run();

foreach (inte_AutoLoader::$classMap_ as $class => $file) {
  try {
    if (is_subclass_of($class, \Module\Event\EventCenterAutoRegister::name())) {
      /**
       * @var \Module\Event\EventCenterAutoRegister $autoRegister
       */
      $autoRegister = new $class();
      $autoRegister->add();
    }
  } catch (Exception $exception){}
}

\Module\Event\EventCenterAutoRegister::createEventCenterAutoEventData();
