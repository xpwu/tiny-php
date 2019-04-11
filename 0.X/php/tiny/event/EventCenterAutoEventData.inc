<?php

namespace Tiny\Event;

/*
 * ------Auto Created By EventCenterAutoRegistrator, DO NOT modify this file------
*/

class EventCenterAutoEventData {
  static public function getHandlers(string $eventID):array {
    if (!array_key_exists($eventID, self::$allHandlers)) {
      return [];
    }

    return self::$allHandlers[$eventID];
  }

  static private $allHandlers = [
		"Tiny\Event\DemoEvent_arg_5"=>[
			"Tiny\Event\DemoListener",
		],
		"Tiny\Event\DemoEvent_all"=>[
			"Tiny\Event\DemoListener",
		],  

  ];
}
