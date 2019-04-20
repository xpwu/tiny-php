<?php


namespace Tiny\Event;


abstract class EventIdFactory {
  public function getId(string $className, string $argId): EventID {
    return new EventID($className . $this->argId($argId));
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
    return "_all";
  }
}

class ArgEventIdFactory extends EventIdFactory {

  protected function argId(string $argId): string {
    return "_arg_".$argId;
  }
}