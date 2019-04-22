<?php

namespace Tiny\DB\Index\Annotation;

use Tiny\AnnotationHelper;

abstract class AllNeedCreateIndex extends AnnotationHelper {

  /**
   * @return AllNeedCreateIndex
   * @throws \Exception
   */
  static public function getImpl():AllNeedCreateIndex {
    $impl = self::getFullClassName();
    if (!class_exists($impl)) {
      throw new \Exception(
        "please add processor: TinyDBIndexAnnotationProcessor with"
        . " \$annotation_processors in project.conf.hphp");
    }
    return new $impl();
  }

  /**
   * @return NeedCreateIndex[]
   */
  abstract public function getAll():array ;
}