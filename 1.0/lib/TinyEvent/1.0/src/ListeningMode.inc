<?php


namespace Tiny\Event;


abstract class ListeningMode {
  protected function __construct() {
  }

  static public function useEventArgs():self {
    return new UseEventArgs();
  }

  static public function notUseEventArgs():self {
    return new NotUseEventArgs();
  }

  abstract public function adjustEventSafely(Event $event):void ;
}

class UseEventArgs extends ListeningMode {
  protected function __construct() {
    parent::__construct();
  }

  // Event 默认方式就是使用Args，同时为了兼容原来的toAll 防止把一个toAll 设置为使用参数,
  // 所以这里不做任何事情
  public function adjustEventSafely(Event $event):void {
  }
}

class NotUseEventArgs extends ListeningMode {
  protected function __construct() {
    parent::__construct();
  }

  public function adjustEventSafely(Event $event):void {
    $event->setIdFactory(new AllEventIdFactory());
  }
}
