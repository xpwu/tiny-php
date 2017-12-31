<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/31
 * Time: 下午4:40
 */

date_default_timezone_set('PRC'); // 设置时区

function exception_error_handler($errno, $errstr, $errfile, $errline ) {
  throw new ErrorException($errstr, 0, $errno, $errfile, $errline);
}
set_error_handler("exception_error_handler");


class Option {
  public $url = "";
  public $headers = [];
  public $interval = 5;
}

function error_info() {
  $info =<<< EOF
usage: -h: show this info;
       -u url: 接收tick的服务器地址；
       -H name value: 添加header, 可多次使用；
       -i interval: 间隔时间

EOF;

  file_put_contents('php://stderr', $info);
}

function parseOption (array $argv, Option $option):bool {
  if (count($argv) == 1) {
    error_info();
    return false;
  }

  $length = count($argv);

  for ($i = 1; $i < $length; ++$i) {

    if ($argv[$i] == '-u' && $i+1 < $length) {
      $option->url = $argv[++$i];
      continue;
    }
    if ($argv[$i] == '-i' && $i+1 < $length) {
      $option->interval = intval($argv[++$i]);
      continue;
    }
    if ($argv[$i] == '-H' && $i+2 < $length) {
      $option->headers[] = $argv[++$i].": ".$argv[++$i];
      continue;
    }

    error_info();
    return false;
  }

  return true;
}

$option = new Option();

if (!parseOption($_SERVER['argv'], $option)) {
  exit(1);
}

function info(string $msg) {
  echo date("Y-m-d H:i:s ")."[ INFO]".$msg."\n";
}

function error(string $msg) {
  echo date("Y-m-d H:i:s ")."[ERROR]".$msg."\n";
}

$option->interval = ($option->interval >= 1)?$option->interval:5;

function tick(Option $t) {
  $curl = curl_init($t->url);
  curl_setopt($curl, CURLOPT_TIMEOUT, 30);
  curl_setopt($curl, CURLOPT_HEADER, false);
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
  if (count($t->headers) != 0) {
    curl_setopt($curl, CURLOPT_HTTPHEADER, $t->headers);
  }
  $res = curl_exec($curl);
  if ($res === false || curl_errno($curl)) {
    error("curl GET error!");
    return;
  }
  curl_close($curl);
}

while (true) {
  info("tick");
  $start = time();
  tick($option);
  $end = time();

  sleep($option->interval - ($end-$start));
}


