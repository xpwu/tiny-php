<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/31
 * Time: 上午2:34
 */

namespace Tiny;


class Log4php extends Logger {

  const LEVEL_MAP = [
    "ALL",
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL",
    "OFF"
  ];

  public function init() {
    \Logger::configure(array(
      'rootLogger' => array(
        'appenders' => array('default'),
      ),
      'appenders' => array(
        'default' => array(
          'class' => 'LoggerAppenderDailyFile',
          'layout' => array(
            'class' => 'LoggerLayoutPattern',
            'params' => array(
              'conversionPattern' => '%date{Y-m-d H:i:s,u} [%5pid] %level %m%n%ex'
            )
          ),
          'params' => array(
            'file' => \Config\Logger::path,
            'append' => true
          )
        )
      )
    ));

    $this->logger_ = \Logger::getRootLogger();
    $this->logger_->setLevel(\LoggerLevel::toLevel(self::LEVEL_MAP[\Config\Logger::level]));
  }

  public function trace(string $message, \Throwable $throwable = null) {
    $this->logger_->trace($this->format($message), $throwable);
  }

  public function debug(string $message, \Throwable $throwable = null) {
    $this->logger_->debug($this->format($message), $throwable);
  }

  public function info(string $message, \Throwable $throwable = null) {
    $this->logger_->info($this->format($message), $throwable);
  }

  public function warn(string $message, \Throwable $throwable = null) {
    $this->logger_->warn($this->format($message), $throwable);
  }

  public function error(string $message, \Throwable $throwable = null) {
    $this->logger_->error($this->format($message), $throwable);
  }

  public function fatal(string $message, \Throwable $throwable = null) {
    $this->logger_->fatal($this->format($message), $throwable);
  }

  private function format(string $message):string {
    $this->getLocationInformation();
    return $this->fullInfo."[uid:".$this->request->uid
      .", api:".$this->request->api."] --- ".$message;
  }

  private $logger_;

}
