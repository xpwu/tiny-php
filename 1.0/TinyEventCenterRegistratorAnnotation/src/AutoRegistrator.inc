<?php


namespace Tiny\Event\Center\Annotation;


use Inte\Annotation;
use Tiny\Event\EventCenter;
use Tiny\Event\Listener;

interface AutoRegistrator extends Annotation {
  function addListeners(EventCenter $eventCenter):void ;
  function registerToEventCenter():EventCenter;
}
