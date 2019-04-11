<?php

/*
 * ------Auto Created By integrate, DO NOT modify this file------
 */


class inte_AutoLoader {

  static public $prefixDir = null;

  /**
   * @return bool
   */
  static function run() {
    if (self::$hasLoad_) {
      return true;
    }
    
    if (self::$prefixDir === null) {
      self::$prefixDir = dirname(__FILE__);
    }

    self::$hasLoad_ = spl_autoload_register( function($classname) {
      if (array_key_exists($classname, self::$classMap_)) {
        require_once (self::$prefixDir.'/'.self::$classMap_[$classname]);
				return true;
			}

			if (array_key_exists($classname, self::$excludeClassMap_)) {
        require_once (self::$excludeClassMap_[$classname]);
				return true;
			}

			return false;
    });
    return self::$hasLoad_;
  }

  static private $hasLoad_ = false;
  static public $classMap_ = [
    'ProjectInit' => "./ProjectInit.inc",
    'Tiny\API' => "./tiny/API.inc",
    'Tiny\HttpStatus' => "./tiny/HttpStatus.inc",
    'Tiny\JsonAPI' => "./tiny/JsonAPI.inc",
    'Tiny\Logger' => "./tiny/Logger.inc",
    'Tiny\Request' => "./tiny/Request.inc",
    'Tiny\Response' => "./tiny/Response.inc",
    'Tiny\DB\CreateIndexInterface' => "./tiny/db/CreateIndexInterface.inc",
    'Tiny\DB\MongoDB' => "./tiny/db/MongoDB.inc",
    'Tiny\DB\MongodbDefault' => "./tiny/db/MongodbDefault.inc",
    'Tiny\DB\Timer' => "./tiny/db/Timer.inc",
    'Tiny\Event\EventIdFactory' => "./tiny/event/Event.inc",
    'Tiny\Event\AllEventIdFactory' => "./tiny/event/Event.inc",
    'Tiny\Event\ArgEventIdFactory' => "./tiny/event/Event.inc",
    'Tiny\Event\Event' => "./tiny/event/Event.inc",
    'Tiny\Event\EventCenter' => "./tiny/event/EventCenter.inc",
    'Tiny\Event\EventCenterAutoRegistrator' => "./tiny/event/EventCenterAutoRegistrator.inc",
    'Tiny\Event\Listener' => "./tiny/event/Listener.inc",
    'Tiny\Event\TimerEvent' => "./tiny/event/TimerEvent.inc",
    'Tiny\Event\DemoEvent' => "./tiny/event/demo/DemoEvent.inc",
    'Tiny\Event\DemoListener' => "./tiny/event/demo/DemoListener.inc",
    'Tiny\Event\DemoListenerAutoRegister5' => "./tiny/event/demo/DemoListener.inc",
    'Tiny\Event\DemoListenerAutoRegisterAll' => "./tiny/event/demo/DemoListener.inc",
    'Tiny\Log4php' => "./tiny/Log4php.inc",
    'Tiny\DB\EventData' => "./tiny/db/EventData.inc",
  ];

  static private $excludeClassMap_ = [
  ];
}

