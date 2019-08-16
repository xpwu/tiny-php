<?php


namespace Tiny\Core;


class Utils {
  private const AllStr = "QWERTYUIOPASDFGHJKLZXCVBNM1234567890qwerty"
    ."uiopasdfghjklzxcvbnm!@#$?|{/:%^&*()-_[]}<>~+=,.";

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

    return sha1(uniqid(str_shuffle(self::AllStr), true)
      . gethostname().microtime());
  }
}