<?php


namespace Tiny\DB;


use Tiny\Deprecated\Logic\MongodbDefaultConfig;

/**
 * Class MongodbDefault
 * @package Tiny\DB
 * @deprecated
 */
class MongodbDefault extends MongoDB {
  function __construct($collection) {
    parent::__construct($collection
      , MongodbDefaultConfig::default_dbname
      , MongodbDefaultConfig::default_addr
      , MongodbDefaultConfig::default_user
      , MongodbDefaultConfig::default_passwd);
  }
}