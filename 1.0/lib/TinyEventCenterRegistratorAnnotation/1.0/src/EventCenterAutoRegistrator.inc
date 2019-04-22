<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/30
 * Time: 下午10:34
 */

namespace Tiny\Event;


use Inte\Annotation;
use Tiny\Event\Center\Annotation\AutoRegistrator;

/**
 * Class EventCenterAutoRegistrator
 * @package Tiny\Event
 * @deprecated
 */
abstract class EventCenterAutoRegistrator implements Annotation, AutoRegistrator {

  /**
   * 返回要自动注册的Listener
   * @return Listener
   */
  abstract protected function listener():Listener ;

   /**
    * @return Listener[]
    */
   function needRegisterListeners(): array {
     return [$this->listener()];
   }

   function registerToEventCenter(): EventCenter {
     return EventCenter::default();
   }
 }
