<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/31
 * Time: 上午1:32
 */

namespace Tiny;


use TinyCore\src\LoggerInfo;

class Request implements LoggerInfo {
  public $data;
  public $api;
  public $uid;
  public $reqID;
  public $httpHeaders = [];

  function info(): string {
    return "uid:" . $this->uid . ", api:" . $this->api . ", reqid:" . $this->reqID;
  }
}
