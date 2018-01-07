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

    ini_set('display_errors','Off');
    error_reporting(E_ALL);
    ini_set('log_errors', 'On');
    $errlog = ini_get("error_log");
    if ($errlog == "" || $errlog == false) {
      ini_set('error_log', "error.log");
    }

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

    $response = new Tiny\Response();
    unset($response->data);
    try {
      // ----- request -----
      $request = new Tiny\Request();
      Logger::getInstance()->setRequest($request);

      $request->api = explode('?', $_SERVER["REQUEST_URI"]);
      $api = explode('/', $request->api[0]);
      if (count($api) > 0 && $api[0] == '') {
        array_shift($api);
      }
      $request->api = implode('/', $api);
      $api = implode('\\', $api);
      $request->data = file_get_contents("php://input");
      $request->httpHeaders = $_SERVER;
      $request->uid = "";

      // ----- api -----

      Logger::getInstance()->info("start");

      if (!class_exists($api)) {
        $response->httpStatus = \Tiny\HttpStatus::NOT_FOUND;
        $response->httpStatusMsg = "API Not Found";
      } else {
          /**
           * @var $api Tiny\API
           */
          $api = new $api;
          $api->process($request, $response);
      }
    } catch (Exception $e) {
      $response->httpStatus = \Tiny\HttpStatus::FAILED;
      $response->httpStatusMsg = "PHP Run Error";
      Logger::getInstance()->fatal("500 PHP Run Error", $e);
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
