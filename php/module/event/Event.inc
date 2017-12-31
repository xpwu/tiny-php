<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/29
 * Time: 下午6:55
 */

namespace Module\Event;

use DB\EventData;

abstract class EventIdFactory {
  public function getId(string $className, string $argId): string {
    return $className . $this->argId($argId);
  }

  abstract protected function argId(string $argId): string ;
}

/*
 *  特别注意：无论 $argId 的取值是什么，AllEventIdFactory 与 ArgEventIdFactory
 *  返回的 argId() 都不能相同，否则当$argId为空字符串时，AllEventId 将等于 ArgEventId，
 *  这将导致这类事件的回调被执行两次。
 */

class AllEventIdFactory extends EventIdFactory {

  protected function argId(string $argId): string {
    // TODO: Implement argId() method.
    return "_all";
  }
}

class ArgEventIdFactory extends EventIdFactory {

  protected function argId(string $argId): string {
    // TODO: Implement argId() method.
    return "_arg_".$argId;
  }
}


class Event {
  /**
   * Event constructor.
   * @param string $argId
   * $argId  子事件中，参与事件编码的参数 组合成的字符串，
   *      如果参数无需参与Id编码，直接传入空字符串。
   */
  function __construct(string $argId) {
    $this->idFactory_ = new ArgEventIdFactory();
    $this->argId_ = $argId;
  }

  public function getId(): string {
    return $this->idFactory_->getId(get_class($this), $this->argId_);
  }

  protected function setIdFactory(EventIdFactory $eventIdFactory) {
    $this->idFactory_ = $eventIdFactory;
  }

  /**
   * @return array[['event'=>Event, 'handlers'=>[]], ...]
   */
  public function getHandlers():array {
    $this->setIdFactory(new AllEventIdFactory());
    $eventData = new EventData($this->getId());
    $handlers1 = $eventData->getHandlers();
    $handlers2 = EventCenterAutoEventData::getHandlers($this->getId());

    $this->setIdFactory(new ArgEventIdFactory());
    $eventData = new EventData($this->getId());
    $handlers3 = $eventData->getHandlers();
    $handlers4 = EventCenterAutoEventData::getHandlers($this->getId());

    return [['event'=>$this, 'handlers'=>array_merge($handlers1
      , $handlers2, $handlers3, $handlers4)]];
  }

  public function toAll():void {
    $this->setIdFactory(new AllEventIdFactory());
  }

  public function handlerError() {}

  public function handlerOver() {}

  public function addHandler(string $handler) {
    $eventData = new EventData($this->getId());
    $eventData->addHandler($handler);
  }

  public function removeHandler(string $handler) {
    $eventData = new EventData($this->getId());
    $eventData->delHandler($handler);
  }

  private $idFactory_;
  private $argId_;

}
