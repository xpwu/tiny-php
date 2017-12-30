<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/29
 * Time: 下午6:56
 */

namespace Module\Event;

use DB\Timer;

class TimerEvent extends Event {
  function __construct(int $interval_s, string $unionID=null) {
    parent::__construct("");

    $this->interval_ = $interval_s;
    $this->timer_ = new Timer($unionID);
  }

  /**
   * @return array[['event'=>Event, 'handlers'=>[]], ...]
   */
  public function getHandlers(): array {
    $now = time();
    $timers = Timer::lessThan($now, 50);

    $result = [];
    /**
     * @var $timer Timer
     */
    foreach ($timers as $timer) {
      $timerEvent = new TimerEvent($this->interval_);
      $timerEvent->timer_ = $timer;
      $timerEvent->runningTimestamp_ = $now;

      $result[] = ['event'=>$timerEvent, 'handlers'=>[$timer->getHandler()]];
    }

    return $result;
  }

  public function clone(int $interval_s):TimerEvent {
    $event = new TimerEvent($interval_s);
    $event->timer_ = $this->timer_;
    return $event;
  }

  public function addHandler(string $handler) {
    $now = time();
    $this->timer_->set($this->interval_ + $now, $handler);
  }

  public function removeHandler(string $handler) {
    $this->timer_->delForce();
  }

  public function handlerError() {
    $this->timer_->retry();
  }

  public function handlerOver() {
    $this->timer_->delIfBefore($this->runningTimestamp_);
  }

  private $interval_;
  private $timer_;
  private $runningTimestamp_;
}

