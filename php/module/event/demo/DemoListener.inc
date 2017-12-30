<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/31
 * Time: 上午12:10
 */

namespace Module\Event;


class DemoListener extends Listener {

  function __construct(DemoEvent $event) {
    parent::__construct($event);

    $this->event_ = $event;
  }

  protected function handler() {
    // TODO: Implement handler() method.
    echo $this->event_->getIndex();
  }

  private $event_;
}

class DemoListenerAutoRegister5 extends EventCenterAutoRegister {
  /**
   * 返回要自动注册的Listener
   * @return Listener
   */
  protected function listener(): Listener {
    // TODO: Implement listener() method.

    return new DemoListener(new DemoEvent(5));
  }
}

class DemoListenerAutoRegisterAll extends EventCenterAutoRegister {
  /**
   * 返回要自动注册的Listener
   * @return Listener
   */
  protected function listener(): Listener {
    // TODO: Implement listener() method.

    return new DemoListener((new DemoEvent(0))->toAll());
  }
}

