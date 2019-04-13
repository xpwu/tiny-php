<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/30
 * Time: 下午10:34
 */

namespace Tiny\Event;


use Tiny\Event\Center\DefaultName;
use Tiny\Event\Center\Name;

abstract class EventCenterAutoRegistrator {

  /**
   * 返回要自动注册的Listener
   * @return Listener
   */
  abstract protected function listener():Listener ;

  protected function eventCenterName(): Name{
    return DefaultName::to();
  }

}
