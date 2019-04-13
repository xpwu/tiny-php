<?php


namespace Tiny\Event\Center;


class AutoEventData {
  static public function getNameSpace(Name $name):string {
    return  __NAMESPACE__."\\$name";
  }

  static public function getClassName():string {
    return "AutoEventData";
  }

  static public function getFileDirAndName(Name $name):string {
    $name = explode('\\', $name);
    $name[] = self::getClassName();
    return implode('/', $name);
  }

  static private function getFullClassName(Name $name) {
    return self::getNameSpace($name) . "\\" . self::getClassName();
  }

  static public function getHandlerForName(string $eventId, Name $name):array {
    /**
     * @var AutoEventData $cls
     */
    $cls = self::getFullClassName($name);
    return $cls::getHandlers($eventId);
  }

  /**
   * @param string $eventID
   * @return string[]
   */
  static protected function getHandlers(string $eventID):array {
    if (!array_key_exists($eventID, static::$allHandlers)) {
      return [];
    }

    return static::$allHandlers[$eventID];
  }

  static protected $allHandlers = [

    "Tiny\Event\DemoEvent_arg_5"=>[
      "Tiny\Event\DemoListener",
    ],
    "Tiny\Event\DemoEvent_all"=>[
      "Tiny\Event\DemoListener",
    ],

  ];

}