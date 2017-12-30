<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/30
 * Time: 上午1:29
 */

namespace DB;


use MongoDB\BSON\ObjectID;
use MongoDB\Driver\BulkWrite;
use MongoDB\Driver\Command;
use MongoDB\Driver\Query;

class Timer extends MongodbDefault implements CreateIndexInterface {

  const ID = "_id";
  const TimeStamp = "timestamp";
  const handler = 'api';
  const retry = "retry";


  function __construct(string $id = null) {
    parent::__construct(\Config::Timer_collection_name);

    if ($id === null) {
      $id = new ObjectID();
    }
    $this->id_ = $id."";
  }

  /**
   * @param int $timestamp
   * @param int $limit
   * @return array[Timer]
   */
  static public function lessThan(int $timestamp_s, int $limit):array {
    $timer = new Timer();
    $manager = $timer->getManager();

    $filter = [self::TimeStamp=>['$lte'=>$timestamp_s]];
    $cursor = $manager->executeQuery($timer->getNs(), new Query($filter
      , ['limit' => $limit]));

    $result = [];

    foreach ($cursor as $item) {
      $timer = new Timer($item->{self::ID});
      $timer->timestamp_ = $item->{self::TimeStamp};
      $timer->handler_ = $item->{self::handler};

      $result[] = $timer;
    };

    return $result;
  }

  public function retry() {
    $manager = $this->getManager();
    $bulk = new BulkWrite();
    $bulk->update([self::ID=>$this->id_]
      , ['$inc'=>[
        self::retry=>1
      ]]);
    $manager->executeBulkWrite($this->getNs(), $bulk);
    $this->retry_ ++;
  }

  public function set(int $timestamp_s, string $handler) {
    $this->handler_ = $handler;
    $this->timestamp_ = $timestamp_s;
    $this->retry_ = 0;

    $filter = [self::ID => $this->id_];
    $set = [
      self::TimeStamp=>$this->timestamp_
      , self::handler=>$this->handler_
      , self::retry=>$this->retry_
    ];

    $bulk = new BulkWrite();
    $bulk->update($filter
      , ['$set'=>$set], ['upsert'=>true]);
    $this->getManager()->executeBulkWrite($this->getNs(), $bulk);
  }

  public function delForce() {
    $manager = $this->getManager();
    $filter = [self::ID => $this->id_];
    $bulk = new BulkWrite();
    $bulk->delete($filter);
    try {
      $manager->executeBulkWrite($this->getNs(), $bulk);
    } catch (\Exception $e) {
      // NOT TO DO
    }
  }

  public function delIfBefore(int $timestamp_s) {
    $manager = $this->getManager();
    $filter = [self::ID => $this->id_, self::TimeStamp=>['$lte'=>$timestamp_s]];
    $bulk = new BulkWrite();
    $bulk->delete($filter);
    try {
      $manager->executeBulkWrite($this->getNs(), $bulk);
    } catch (\Exception $e) {
      // NOT TO DO
    }
  }

  static public function delAllBefore(int $timestamp_s) {
    $timer = new Timer();
    $manager = $timer->getManager();
    $filter = [self::TimeStamp=>['$lte'=>$timestamp_s]];
    $bulk = new BulkWrite();
    $bulk->delete($filter);
    try {
      $manager->executeBulkWrite($timer->getNs(), $bulk);
    } catch (\Exception $e) {
      // NOT TO DO
    }
  }

  public function getHandler(): string {
    return $this->handler_;
  }

  static public function createIndex() {
    $timer = new Timer();
    $cmd = [];
    $cmd['createIndexes'] = $timer->getCol();
    $cmd['indexes'] = [
      [
        'key'=>[self::TimeStamp=>1]
        , 'name'=>"timer_timestamp_1"
      ]
    ];

    $manager = $timer->getManager();
    try {
      $manager->executeCommand($timer->getDB(), new Command($cmd));
    } catch (\Exception $e) {
//      $timer->logger()->error("Timer.InitDB error!", $e);
      return;
    }
  }

  private $id_;
  private $handler_;
  private $timestamp_; // unit: s
  private $retry_;

}
