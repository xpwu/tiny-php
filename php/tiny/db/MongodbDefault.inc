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
      , \Config::MongoDB_default_dbname
      , \Config::MongoDB_default_addr
      , \Config::MongoDB_default_user
      , \Config::MongoDB_default_passwd);
  }
}
