<?php


namespace Tiny;


class AnnotationHelper {
  static public function getNameSpace(?string $needHelpClass = null):string {
    if ($needHelpClass === null) {
      $needHelpClass = static::class;
    }

    $pos = strrpos($needHelpClass, "\\");
    if ($pos === false) {
      return "";
    }

    return  substr($needHelpClass, 0, $pos);
  }

  static public function getImplClassName(?string $needHelpClass = null):string {
    if ($needHelpClass === null) {
      $needHelpClass = static::class;
    }

    $pos = strrpos($needHelpClass, "\\");
    if ($pos === false) {
      $pos = 0;
    }

    return  substr($needHelpClass, $pos);
  }

  static public function getFileDirAndName(?string $needHelpClass = null):string {
    $name = explode('\\', self::getNameSpace($needHelpClass));
    $name[] = self::getImplClassName($needHelpClass) . '.inc';
    return implode('/', $name);
  }

  static public function getFullClassName(?string $needHelpClass = null) {
    return self::getNameSpace($needHelpClass)
      . "\\" . self::getImplClassName($needHelpClass);
  }
}