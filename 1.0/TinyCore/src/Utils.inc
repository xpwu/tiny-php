<?php


namespace Tiny\Core;


class Utils {
  static public function stringArray2string(array $strings):string {
    return implode(",", array_map(function (string $value){
      return PHP_EOL . "'" . $value . "'";
    }, $strings));
  }
}