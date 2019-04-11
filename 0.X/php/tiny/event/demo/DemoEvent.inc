<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/31
 * Time: 上午12:09
 */

namespace Tiny\Event;


class DemoEvent extends Event {
 function __construct(int $index) {
   parent::__construct($index);
 }

 public function getIndex() {
   return $this->index_;
 }

 private $index_;
}