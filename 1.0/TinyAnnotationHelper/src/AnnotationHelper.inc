<?php


namespace Tiny;


class AnnotationHelper {

  static public function getNameSpace(
    ?string $shouldCreateFileClass = null):string {

    if ($shouldCreateFileClass === null) {
      $shouldCreateFileClass = static::class;
    }

    try {
      $clazz = new \ReflectionClass($shouldCreateFileClass);
    } catch (\ReflectionException $e) {
      Logger::getInstance()->fatal("", $e);
    }
    return $clazz->getNamespaceName();
  }

  static public function getCreatedClassName(?string $shouldCreateFileClass = null
    , string  $suffix = "Impl"):string {
    if ($shouldCreateFileClass === null) {
      $shouldCreateFileClass = static::class;
    }

    try {
      $clazz = new \ReflectionClass($shouldCreateFileClass);
    } catch (\ReflectionException $e) {
      Logger::getInstance()->fatal("", $e);
    }
    return $clazz->getShortName() . $suffix;
  }

  static public function getFileDirAndName(
    ?string $shouldCreateFileClass = null
    , string $fileSuffix = ".inc"):string {

    $name = explode('\\', self::getNameSpace($shouldCreateFileClass));
    $name[] = self::getCreatedClassName($shouldCreateFileClass) . $fileSuffix;
    return implode('/', $name);
  }

  static public function getFullClassName(?string $needHelpClass = null
    , string $suffix = "Impl") {

    if ($needHelpClass === null) {
      $needHelpClass = static::class;
    }

    return $needHelpClass . $suffix;
  }
}