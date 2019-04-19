<?php


namespace Tiny\Event\Center;


use Tiny\AnnotationHelper;
use Tiny\Event\EventID;
use Tiny\Event\Listener;

class AutoRegistratorHelper extends AnnotationHelper {
  static public function getRegistratorHelper(Name $name):AutoRegistratorHelper {
    $registrator = self::getFullClassName($name);
    if (!class_exists($registrator)) {
      return new AutoRegistratorHelper();
    }

    return new $registrator();
  }

  /**
   * @return Listener[]
   */
  public function getAllListenerByEventID(EventID $eventId):array {
    return [];
  }
}