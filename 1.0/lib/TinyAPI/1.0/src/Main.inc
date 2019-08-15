<?php

/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/29
 * Time: 下午6:44
 */

namespace Tiny\API;

use Tiny\API;
use Tiny\Core\Utils;
use Tiny\Logger;
use Tiny\Request;
use Tiny\Response;

class Main {

  static public function main() {

    date_default_timezone_set('PRC'); // 设置时区

    ini_set('display_errors','Off');
    error_reporting(E_ALL);
    ini_set('log_errors', 'On');
    $errLog = ini_get("error_log");
    if ($errLog == "" || $errLog == false) {
      ini_set('error_log', "error.log");
    }

    set_error_handler(function($errno, $errStr, $errFile, $errLine ) {
      /**
       * https://www.php.net/manual/zh/language.operators.errorcontrol.php
       * 错误控制运算符：@ 标注的忽略错误不再输出
       */
      if (error_reporting() === 0) {
        return false;
      }

      throw new \ErrorException($errStr, 0, $errno, $errFile, $errLine);
    });

    $logger = Config::logger;
    Logger::setConcreteLogger(new $logger());

    $response = new Response();
    unset($response->data);
    try {
      // ----- request -----
      $request = new Request();
      Logger::getInstance()->setAdditionalInfo($request);

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
      $request->reqID = @$_SERVER['HTTP_REQID']??Utils::uniqRandomStr();

      $response->httpHeaders['REQID'] = $request->reqID;

      // ----- api -----

      Logger::getInstance()->info("start");

      if (!class_exists($api)) {
        $response->httpStatus = \Tiny\HttpStatus::NOT_FOUND;
        $response->httpStatusMsg = "API Not Found";
      } else {
          /**
           * @var $api API
           */
          $api = new $api;
          $api->process($request, $response);
      }
    } catch (\Exception $e) {
      $response->httpStatus = \Tiny\HttpStatus::FAILED;
      $response->httpStatusMsg = "PHP Run Error";
      Logger::getInstance()->fatal("500 PHP Run Error", $e);
    }

    // ------ response -------
    Logger::getInstance()->info("end");

    if ($response->httpStatus != \Tiny\HttpStatus::SUC) {
      Logger::getInstance()->fatal($response->httpStatusMsg);
      header("HTTP/1.1 ". $response->httpStatus." ".$response->httpStatusMsg);
      header('REQID: '. $request->reqID);
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
