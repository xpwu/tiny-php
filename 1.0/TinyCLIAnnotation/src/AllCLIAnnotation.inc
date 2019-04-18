<?php


namespace Tiny\CLI\Annotation;


use Tiny\CLIAnnotation;

abstract class AllCLIAnnotation {
  static public function getNameSpace():string {
    return  __NAMESPACE__;
  }

  static public function getImplClassName():string {
    return "AllCLIAnnotationImpl";
  }

  static public function getFileDirAndName():string {
    $name = explode('\\', self::getNameSpace());
    $name[] = self::getImplClassName() . '.inc';
    return implode('/', $name);
  }

  static private function getFullClassName() {
    return self::getNameSpace() . "\\" . self::getImplClassName();
  }

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