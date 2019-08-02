<?php


namespace Tiny\Core;


class Utils {
  static public function stringArray2string(array $strings):string {
    return implode(",", array_map(function (string $value){
      return PHP_EOL . "'" . $value . "'";
    }, $strings));
  }

  static public function fullClassNameToFullFileName(
    string $className, string $ext = ".inc"):string {
    $name = explode('\\', $className);
    return implode('/', $name).$ext;
  }

  static function uniqRandomStr():string {
    define("AllStr", "QWERTYUIOPASDFGHJKLZXCVBNM1234567890qwertyuiopasdfghjklzxcvbnm!@#$?|{/:%^&*()-_[]}<>~+=,.");

    return sha1(uniqid(str_shuffle(AllStr), true)
      . gethostname().microtime());
  }
}