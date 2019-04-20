<?php


namespace Tiny\CLI\Annotation;


use Tiny\AnnotationHelper;
use Tiny\CLIAnnotation;

abstract class AllCLIAnnotation extends AnnotationHelper {

  /**
   * @return AllCLIAnnotation
   * @throws \Exception
   */
  static public function getImpl():AllCLIAnnotation {
    $impl = self::getFullClassName();
    if (!class_exists($impl)) {
      throw new \Exception("please add processor: TinyCLIAnnotationProcessor");
    }
    return new $impl();
  }

  /**
   * @return CLIAnnotation[]
   */
  abstract public function getAllCLIAnnotation():array ;

}