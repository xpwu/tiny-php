<?php


namespace Tiny\DB\Index\Annotation;



use Inte\MetaAnnotation\Annotation;

interface NeedCreateIndex extends Annotation {
  static function createIndex():void ;
  static function description():string ;
}