<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/30
 * Time: 下午10:34
 */

namespace Tiny\Event;


abstract class EventCenterAutoRegistrator {

  static public function name() {
    return get_class();
  }

  static private $allListeners = [];

  /**
   * 返回要自动注册的Listener
   * @return Listener
   */
  abstract protected function listener():Listener ;

  public function add() {
    $listener = $this->listener();
    $eventName = $listener->getEvent()->getId();
    if (!key_exists($eventName, self::$allListeners)) {
      self::$allListeners[$eventName] = [];
    }
    array_push(self::$allListeners[$eventName], $listener->getClassSign());
  }

  static public function registerAllListener() {
    foreach (\inte_AutoLoader::$classMap_ as $class => $file) {
      try {
        if (is_subclass_of($class, self::name())) {
          /**
           * @var \Tiny\Event\EventCenterAutoRegistrator $autoRegistrator
           */
          $autoRegistrator = new $class();
          $autoRegistrator->add();
        }
      } catch (\Exception $exception){}
    }
  }

  static public function getHandlers(string $eventID) {
    // use registerAllListener
    if (array_key_exists($eventID, self::$allListeners)) {
      return self::$allListeners[$eventID];
    }

    // use buildAutoEventData.sh
    if (class_exists('Tiny\Event\EventCenterAutoEventData')) {
      return EventCenterAutoEventData::getHandlers($eventID);
    }

    return [];
  }

  static public function createEventCenterAutoEventData() {
    $name = dirname(__FILE__)."/EventCenterAutoEventData.inc";
    $content = <<< EOF
<?php

namespace Tiny\Event;

/*
 * ------Auto Created By EventCenterAutoRegister, DO NOT modify this file------
*/

class EventCenterAutoEventData {
  static public function getHandlers(string \$eventID):array {
    if (!array_key_exists(\$eventID, self::\$allHandlers)) {
      return [];
    }

    return self::\$allHandlers[\$eventID];
  }

  static private \$allHandlers = [
EOF;

    foreach (self::$allListeners as $event=>$listeners) {
      $content .= "\n\t\t\"" . $event . "\"=>[\n\t\t\t";

      foreach ($listeners as $listener) {
        $content .= "\"" . $listener . "\",";
      }

      $content .= "\n\t\t],";
    }

    $content .= <<< EOF
  \n
  ];
}

EOF;

    $fp = fopen($name, 'w');
    fwrite($fp, $content);
    fclose($fp);
  }

}
