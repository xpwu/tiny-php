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

  public function prepare() {
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
  }

  static public function main() {
    date_default_timezone_set('PRC'); // 设置时区

    try {
      /**
       * Options 必须是用到自己类之前的第一句代码，主要是要
       * 加载配置文件，如果在运行其他类时(尤其是logger)加载了配置配置
       * 中的类，将造成无法加载配置文件
       *
       */
      $options = new Options();

      $main = new Main();
      $main->prepare();

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