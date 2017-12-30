<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/31
 * Time: 上午2:34
 */

namespace Base;


class Log4php extends Logger {

  public function init() {
    \Logger::configure(array(
      'rootLogger' => array(
        'appenders' => array('default'),
      ),
      'appenders' => array(
        'default' => array(
          'class' => 'LoggerAppenderFile',
          'layout' => array(
            'class' => 'LoggerLayoutPattern',
            'params' => array(
              'conversionPattern' => '%date{Y-m-d H:i:s,u} [%5pid] %C.%M(...%.-25F:%L) %level --- %m%n%ex'
            )
          ),
          'params' => array(
            'file' => \Config::Logger_path,
            'append' => true
          )
        )
      )
    ));

    $this->logger_ = \Logger::getRootLogger();
    $this->logger_->setLevel(\LoggerLevel::toLevel(\Config::Logger_level));
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

  private function format(string $message) {

  }

  private $logger_;

}
