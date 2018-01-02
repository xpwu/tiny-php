<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/30
 * Time: 上午1:29
 */

namespace Tiny\DB;


use MongoDB\BSON\ObjectID;
use MongoDB\Driver\BulkWrite;
use MongoDB\Driver\Command;
use MongoDB\Driver\Query;
use Tiny\Logger;

class Timer extends MongodbDefault implements CreateIndexInterface {

  const ID = "_id";
  const TimeStamp = "timestamp";
  const handler = 'api';
  const retry = "retry";
  const context = "context";
  const interval = "interval";


  function __construct(string $id = null) {
    parent::__construct(\Config\MongoDB::Timer_collection_name);

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
      $timer->interval_ = $item->{self::interval};
      $timer->retry_ = $item->{self::retry};
      $timer->context_ = $item->{self::context};

      $result[] = $timer;
    }

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

  public function set(int $timestamp_s, string $handler, string $context, int $interval_s) {
    $this->handler_ = $handler;
    $this->timestamp_ = $timestamp_s;
    $this->retry_ = 0;
    $this->context_ = $context;
    $this->interval_ = $interval_s;

    $filter = [self::ID => $this->id_];
    $set = [
      self::TimeStamp=>$this->timestamp_
      , self::handler=>$this->handler_
      , self::retry=>$this->retry_
      , self::context=>$this->context_
      , self::interval=>$this->interval_
    ];

    $bulk = new BulkWrite();
    $bulk->update($filter
      , ['$set'=>$set], ['upsert'=>true]);
    $this->getManager()->executeBulkWrite($this->getNs(), $bulk);
  }

  public function delForce() {
    $filter = [self::ID => $this->id_];
    $bulk = new BulkWrite();
    $bulk->delete($filter);
    try {
      $this->getManager()->executeBulkWrite($this->getNs(), $bulk);
    } catch (\Exception $e) {
      Logger::getInstance()->fatal("timer delForce error", $e);
    }
  }

  public function delIfBefore(int $timestamp_s) {
    $filter = [self::ID => $this->id_, self::TimeStamp=>['$lte'=>$timestamp_s]];
    $bulk = new BulkWrite();
    $bulk->delete($filter);
    try {
      $this->getManager()->executeBulkWrite($this->getNs(), $bulk);
    } catch (\Exception $e) {
      Logger::getInstance()->fatal("timer delIfBefore error", $e);
    }
  }

  static public function delAllBefore(int $timestamp_s) {
    $timer = new Timer();
    $filter = [self::TimeStamp=>['$lte'=>$timestamp_s]];
    $bulk = new BulkWrite();
    $bulk->delete($filter);
    try {
      $timer->getManager()->executeBulkWrite($timer->getNs(), $bulk);
    } catch (\Exception $e) {
      Logger::getInstance()->fatal("timer delAllBefore error", $e);
    }
  }

  public function getHandler(): string {
    return $this->handler_;
  }

  public function getContext(): string {
    return $this->context_;
  }

  public function getInterval(): int {
    return $this->interval_;
  }

  public function getID():string {
    return $this->id_.":".$this->timestamp_;
  }

  static public function createIndex() {
    Logger::getInstance()->debug(__CLASS__."::createIndex start");
    $timer = new Timer();
    $cmd = [];
    $cmd['createIndexes'] = $timer->getCol();
    $cmd['indexes'] = [
      [
        'key'=>[self::TimeStamp=>1]
        , 'name'=>"timer_timestamp_1"
      ]
    ];

    try {
      $manager = $timer->getManager();
      $manager->executeCommand($timer->getDB(), new Command($cmd));
    } catch (\Exception $e) {
      Logger::getInstance()->error("Timer.createIndex error!", $e);
      return;
    }
    Logger::getInstance()->debug(__CLASS__."::createIndex end");
  }

  /**
   * @var string
   */
  private $id_;
  private $handler_;
  private $timestamp_; // unit: s
  private $retry_;
  private $context_;
  private $interval_;
}
