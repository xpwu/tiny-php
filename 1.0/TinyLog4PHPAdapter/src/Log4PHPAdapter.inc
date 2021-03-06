<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/31
 * Time: 上午2:34
 */

namespace Tiny;



class Log4PHPAdapter extends Logger {

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
            'file' => ini_get("error_log"),
            'append' => true
          )
        )
      )
    ));

    $this->logger_ = \Logger::getRootLogger();
    $this->logger_->setLevel(\LoggerLevel::toLevel(
      self::LEVEL_MAP[$this->level->value()]));
  }

  public function trace(string $message, ?\Throwable $throwable = null) {
    $this->logger_->trace($this->format($message), $throwable);
  }

  public function debug(string $message, ?\Throwable $throwable = null) {
    $this->logger_->debug($this->format($message), $throwable);
  }

  public function info(string $message, ?\Throwable $throwable = null) {
    $this->logger_->info($this->format($message), $throwable);
  }

  public function warn(string $message, ?\Throwable $throwable = null) {
    $this->logger_->warn($this->format($message), $throwable);
  }

  public function error(string $message, ?\Throwable $throwable = null) {
    $this->logger_->error($this->format($message), $throwable);
  }

  public function fatal(string $message, ?\Throwable $throwable = null) {
    $this->logger_->fatal($this->format($message), $throwable);
  }

  private function format(string $message):string {
    $this->getLocationInformation();
    $add = "";
    if ($this->additionalInfo !== null) {
      $add = $this->additionalInfo->info();
    }
    return $this->fullInfo."[". $add ."] --- ".$message;
  }

  /**
   * @var \Logger
   */
  private $logger_;

}
