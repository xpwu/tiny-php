<?php


namespace Tiny\Deprecated\Annotation;


use Tiny\AnnotationHelper;
use Tiny\DB\CreateIndexInterface;

abstract class CreateAllIndexHelper extends AnnotationHelper {
  static public function getImpl():CreateAllIndexHelper {
    $impl = self::getFullClassName();
    if (!class_exists($impl)) {
      throw new \Exception("please add processor: TinyDeprecatedAnnotationProcessor");
    }
    return new $impl();
  }

  /**
   * @return CreateIndexInterface[]
   */
  abstract public function getAll():array;
}