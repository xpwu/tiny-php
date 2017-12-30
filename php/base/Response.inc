<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/31
 * Time: 上午1:32
 */

namespace Base;


class HttpStatus {
  const SUC = 200;
  const ARGS_FORMAT_ERROR = 400;
  const NOT_FOUND = 404;
  const ARGS_ERROR = 415;
  const FAILED = 500;
}


class Response {
  function __construct() {
    $this->httpStatus = HttpStatus::SUC;
  }

  public $data;
  public $httpStatus;
  public $httpStatusMsg;
  public $httpHeaders = [];
}
