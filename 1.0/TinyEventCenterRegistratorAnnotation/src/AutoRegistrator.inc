<?php


namespace Tiny\Event\Center\Annotation;



use Inte\MetaAnnotation\Annotation;
use Tiny\Event\EventCenter;

interface AutoRegistrator extends Annotation {
  function addListeners(EventCenter $eventCenter):void ;
  function registerToEventCenter():EventCenter;
}
