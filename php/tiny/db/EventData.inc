<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/30
 * Time: 下午5:27
 */

namespace Tiny\DB;


use MongoDB\Driver\BulkWrite;
use MongoDB\Driver\Query;

class EventData extends MongodbDefault {

  const name = "_id";
  const data = "data";

  function __construct(string $name) {
    parent::__construct(\Config\MongoDB::Event_collection_name);

    $this->name_ = $name;
  }

  public function addHandler(string $handler) {
    $manager = $this->getManager();
    $filter = [self::name=>$this->name_];
    $bulk = new BulkWrite();
    $bulk->update($filter, ['$addToSet'=>[self::data=>$handler]], ['upsert'=>true]);
    $manager->executeBulkWrite($this->getNs(), $bulk);
  }

  public function delHandler(string $handler) {
    $manager = $this->getManager();
    $filter = [self::name=>$this->name_];
    $bulk = new BulkWrite();
    $bulk->update($filter, ['$pull'=>[self::data=>$handler]]);
    $manager->executeBulkWrite($this->getNs(), $bulk);

    $filter = [self::name=>$this->name_, self::data=>['$size'=>0]];
    $bulk = new BulkWrite();
    $bulk->delete($filter);
    $manager->executeBulkWrite($this->getNs(), $bulk);
  }

  /**
   * @return array[string]
   */
  public function getHandlers():array {
    $manager = $this->getManager();
    $filter = [self::name=>$this->name_];

    $cursor = $manager->executeQuery($this->getNs(), new Query($filter));
    $result = $cursor->toArray();
    return $result[0]->{self::data};
  }

  private $name_;

}