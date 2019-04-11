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

inte_AutoLoader::$prefixDir = dirname(__FILE__)."/../..";
inte_AutoLoader::run();

\Tiny\Event\EventCenterAutoRegistrator::registerAllListenerWithPcntl();

\Tiny\Event\EventCenterAutoRegistrator::createEventCenterAutoEventData();
