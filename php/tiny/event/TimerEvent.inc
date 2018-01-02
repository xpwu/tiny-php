<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/29
 * Time: 下午6:56
 */

namespace Tiny\Event;

use Tiny\DB\Timer;

class TimerEvent extends Event {
  function __construct(int $interval_s, array $context, string $unionID=null) {
    parent::__construct("");

    $this->interval_ = $interval_s;
    $this->timer_ = new Timer($unionID);
    $this->context_ = $context;
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
      $timerEvent = new TimerEvent($timer->getInterval()
        , json_decode($timer->getContext(), true)
        , $timer->getID());
      $timerEvent->runningTimestamp_ = $now;

      $result[] = ['event'=>$timerEvent, 'handlers'=>[$timer->getHandler()]];
    }

    return $result;
  }

  public function getId(): string {
    return "TimerEvent:".$this->timer_->getID();
  }

  public function canAutoRegister():bool {
    return false;
  }

//  public function clone(int $interval_s):TimerEvent {
//    $event = new TimerEvent($interval_s);
//    $event->timer_ = $this->timer_;
//    return $event;
//  }

  public function addHandler(string $handler) {
    $now = time();
    $this->timer_->set($this->interval_ + $now
      , $handler, $this->interval_
      , json_encode($this->context_));
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

  public function getContext():array  {
    return $this->context_;
  }

  private $interval_;
  private $timer_;
  private $runningTimestamp_;
  private $context_;
}

