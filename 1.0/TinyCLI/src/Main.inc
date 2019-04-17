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

//    function exception_error_handler($errno, $errstr, $errfile, $errline ) {
//       throw new ErrorException($errstr, 0, $errno, $errfile, $errline);
//    }
//    set_error_handler("exception_error_handler");

    Logger::setConcreteLogger(new StdLogger());
    $options = new Options();
    try {
      $options->getCommand()->run();
      exit(0);
    }catch (OK $error) {
      exit(0);
    }catch (NormalError $error) {
      fwrite(STDERR, $error);
      exit(-1);
    }

  }
}