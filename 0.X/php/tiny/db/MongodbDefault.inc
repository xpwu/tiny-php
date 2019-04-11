<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/30
 * Time: 下午3:04
 */

namespace Tiny\DB;


class MongodbDefault extends MongoDB {
  function __construct($collection) {
    parent::__construct($collection
      , \Config\MongoDB::default_dbname
      , \Config\MongoDB::default_addr
      , \Config\MongoDB::default_user
      , \Config\MongoDB::default_passwd);
  }
}
