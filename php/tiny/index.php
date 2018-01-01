<?php

/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/29
 * Time: 下午6:44
 */

use Tiny\Logger;

class Index {

  static function main() {

    date_default_timezone_set('PRC'); // 设置时区

    function exception_error_handler($errno, $errstr, $errfile, $errline ) {
      throw new ErrorException($errstr, 0, $errno, $errfile, $errline);
    }
    set_error_handler("exception_error_handler");

    // ------ project init ------
    ProjectInit::init();

    // -------init logger -----
    if (!Logger::hasSetConcreteLogger()) {
      require_once (\Config\Logger::log4php_class_file);
      Logger::setConcreteLogger(new \Tiny\Log4php());
    }

    // ----- request -----

    $request = new Tiny\Request();
    Logger::getInstance()->setRequest($request);

    $request->api = explode('?', $_SERVER["REQUEST_URI"]);
    $request->api = explode('/', $request->api[0]);
    if (count($request->api) > 0 && $request->api[0] == '') {
      array_shift($request->api);
    }
    $request->api = implode('\\', $request->api);
    $request->data = file_get_contents("php://input");
    $request->httpHeaders = $_SERVER;
    $request->uid = "";

    // ----- api -----
    $response = new Tiny\Response();
    unset($response->data);

    Logger::getInstance()->info("start");

    if (!class_exists($request->api)) {
      $response->httpStatus = \Tiny\HttpStatus::NOT_FOUND;
      $response->httpStatusMsg = "API Not Found";
    } else {
      try {
        /**
         * @var $api Tiny\API
         */
        $api = new ($request->api)();
        $api->process($request, $response);
      } catch (Exception $e) {
        $response->httpStatus = \Tiny\HttpStatus::FAILED;
        $response->httpStatusMsg = "PHP Run Error";
        Logger::getInstance()->fatal("500 PHP Run Error", $e);
      }
    }

    // ------ response -------
    Logger::getInstance()->info("end");

    if ($response->httpStatus != \Tiny\HttpStatus::SUC) {
      Logger::getInstance()->fatal($response->httpStatusMsg);
      header("HTTP/1.1 ". $response->httpStatus." ".$response->httpStatusMsg);
      return;
    }

    foreach ($response->httpHeaders as $header => $value) {
      header($header.': '.$value);
    }

    if (isset($response->data)) {
      file_put_contents('php://output', $response->data);
    }

  }
}

Index::main();
