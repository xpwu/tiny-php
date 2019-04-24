<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/29
 * Time: 下午6:55
 */

namespace Tiny\Event;



/**
 * Class Event
 * @package Tiny\Event
 */
class Event {
  /**
   * Event constructor.
   * @param string $argId
   * $argId  子事件中，参与事件编码的参数 组合成的字符串，
   *      如果参数无需参与Id编码，不需传入参数。
   */
  public function __construct(EventArg... $eventArgs) {
    self::__constructOld(implode("_", $eventArgs));
  }

  /**
   * @param string $argId
   * @deprecated
   */
  private function __constructOld(string $argId) {
    $this->idFactory_ = new ArgEventIdFactory();
    $this->argId_ = $argId;
  }

  public function getId(): EventID {
    return $this->idFactory_->getId(get_class($this), $this->argId_);
  }

//  public function canAutoRegister():bool {
//    return true;
//  }

  public function setIdFactory(EventIdFactory $eventIdFactory) {
    $this->idFactory_ = $eventIdFactory;
  }

//  /**
//   * @return array[['event'=>Event, 'handlers'=>[]], ...]
//   */
//  public function getHandlers():array {
//    $this->setIdFactory(new AllEventIdFactory());
//    $eventData = new EventData($this->getId());
//    $handlers1 = $eventData->getHandlers();
//    $handlers2 = EventCenterAutoRegistrator::getHandlers($this->getId());
//
//    $this->setIdFactory(new ArgEventIdFactory());
//    $eventData = new EventData($this->getId());
//    $handlers3 = $eventData->getHandlers();
//    $handlers4 = EventCenterAutoRegistrator::getHandlers($this->getId());
//
//    return [['event'=>$this, 'handlers'=>array_merge($handlers1
//      , $handlers2, $handlers3, $handlers4)]];
//  }

  /**
   * @return EventID[]
   */
  public function getAllMayBeIds():array {
    $ret = [];

    $this->setIdFactory(new AllEventIdFactory());
    $ret[] = $this->getId();
    $this->setIdFactory(new ArgEventIdFactory());
    $ret[] = $this->getId();

    return $ret;
  }

  /**
   * 即将废弃，请尽快使用新的代码
   * @deprecated
   */
  public function toAll() {
    $this->setIdFactory(new AllEventIdFactory());
  }

  public function handlerError() {}

  public function handlerOver() {}

//  public function addHandler(string $handler) {
//    $eventData = new EventData($this->getId());
//    $eventData->addHandler($handler);
//  }
//
//  public function removeHandler(string $handler) {
//    $eventData = new EventData($this->getId());
//    $eventData->delHandler($handler);
//  }

  /**
   * @var EventIdFactory
   */
  private $idFactory_;
  /**
   * @var string
   */
  private $argId_;

}
