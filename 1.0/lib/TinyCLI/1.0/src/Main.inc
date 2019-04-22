<?php

namespace Tiny\CLI;


use Tiny\Logger;

/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/3/9
 * Time: 上午11:48
 */


class Main {

  static public function main() {

    date_default_timezone_set('PRC'); // 设置时区

    Logger::setConcreteLogger(new StdLogger());


    set_error_handler(function($errno, $errstr, $errfile, $errline ) {
      /**
       * https://www.php.net/manual/zh/language.operators.errorcontrol.php
       * 错误控制运算符：@ 标注的忽略错误不再输出
       */
      if (error_reporting() === 0) {
        return false;
      }

      Logger::getInstance()->fatal(""
        , new \ErrorException($errstr, 0, $errno, $errfile, $errline));

      return true;
    });


    set_exception_handler(function (\Throwable $exception) {
      Logger::getInstance()->fatal("", $exception);
    });


    try {
      $options = new Options();
      $options->getCommand()->run();
      exit(0);
    }catch (OK $error) {
      exit(0);
    }catch (NormalError $error) {
      fwrite(STDERR, $error);
      exit(254);
    }

  }
}