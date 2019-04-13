<?php


namespace Tiny\Core\Utils;


class Time {
  static public function getCurrentMillSecond():int {
    $millTime = ((int)(microtime(true)*1000))%1000;
    return $millTime;
  }

  static public function getCurrentMillSecondToString():string {
    $millTime = self::getCurrentMillSecond();
    return date("Y-m-d H:i:s").",".$millTime;
  }

}