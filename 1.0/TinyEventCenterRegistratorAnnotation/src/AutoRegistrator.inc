<?php


namespace Tiny\Event\Center\Annotation;


use Inte\Annotation;
use Tiny\Event\EventCenter;
use Tiny\Event\Listener;

interface AutoRegistrator extends Annotation {
  /**
   * @return Listener[]
   */
  function needRegisterListeners():array ;
  function registerToEventCenter():EventCenter;
}