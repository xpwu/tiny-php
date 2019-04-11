<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/31
 * Time: 上午1:32
 */

namespace Tiny;


class Response {
  function __construct() {
    $this->httpStatus = HttpStatus::SUC;
  }

  public $data;
  public $httpStatus;
  public $httpStatusMsg;
  public $httpHeaders = [];
}
