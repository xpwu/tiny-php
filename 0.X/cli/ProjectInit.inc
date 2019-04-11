<?php

/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2018/1/1
 * Time: 下午5:00
 */
class ProjectInit {
  static public function init () {
    // TODO: add project init

    \Tiny\Event\EventCenterAutoRegistrator::registerAllListener();
  }
}