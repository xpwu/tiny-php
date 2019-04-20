<?php


namespace Tiny\Event\Center;


use Tiny\AnnotationHelper;
use Tiny\Event\EventID;
use Tiny\Event\ListenerClassSign;

class AutoRegistratorHelper extends AnnotationHelper {
  static public function getRegistratorHelper(Name $name):AutoRegistratorHelper {
    $registrator = self::getFullClassName($name);
    if (!class_exists($registrator)) {
      return new AutoRegistratorHelper();
    }

    return new $registrator();
  }

  /**
   * @return ListenerClassSign[]
   */
  public function getAllListenerClassSignByEventID(EventID $eventId):array {
    return [];
  }
}