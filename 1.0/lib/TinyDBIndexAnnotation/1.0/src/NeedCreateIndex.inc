<?php


namespace Tiny\DB\Index\Annotation;


use Inte\Annotation;

interface NeedCreateIndex extends Annotation {
  static function createIndex():void ;
  static function description():string ;
}