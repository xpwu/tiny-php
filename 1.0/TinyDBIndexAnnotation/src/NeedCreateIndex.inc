<?php


namespace Tiny\DB\Index\Annotation;


interface NeedCreateIndex {
  static function createIndex();
  static function getDBName();
  static function getCollectionName();
}