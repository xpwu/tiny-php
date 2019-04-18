<?php


namespace Tiny\CLI\Annotation;


use Tiny\CLIAnnotation;

abstract class AllCLIAnnotation {
  static public function getNameSpace():string {
    return  __NAMESPACE__;
  }

  static public function getImplClassName():string {
    return "AllCLIDataImpl";
  }

  static public function getFileDirAndName():string {
    $name = explode('\\', self::getNameSpace());
    $name[] = self::getImplClassName() . '.inc';
    return implode('/', $name);
  }

  static private function getFullClassName() {
    return self::getNameSpace() . "\\" . self::getImplClassName();
  }

  static public function getImpl():AllCLIAnnotation {
    $impl = self::getFullClassName();
    return new $impl();
  }

  /**
   * @return CLIAnnotation[]
   */
  abstract public function getAllCLIAnnotation():array ;

}