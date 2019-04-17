<?php


namespace Tiny\CLI\Annotation;


class AllCLIData {
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

  /**
   * @return string[] array
   * @throws \Exception
   */
  static public function getAllData():array {
    if (!class_exists(self::getFullClassName())) {
      throw new \Exception("please add processor: TinyCLIAnnotationProcessor");
    }


    return self::getFullClassName()::all;
  }
}