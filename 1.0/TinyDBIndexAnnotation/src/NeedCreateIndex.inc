<?php


namespace Tiny\DB\Index\Annotation;


interface NeedCreateIndex {
  static function createIndex():void ;
  static function getDBName():string ;
  static function getCollectionName():string ;
}