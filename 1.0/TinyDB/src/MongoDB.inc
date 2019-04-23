<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/30
 * Time: 上午12:34
 */

namespace Tiny\DB;

use MongoDB\Driver\Manager;

class MongoDB {
  function __construct(string $collection
    , string $dbName
    , string $addr
    , string $user
    , string $passwd) {

    $this->col_ = $collection;
    $this->addr_ = $addr;
    $this->manager_ = null;
    $this->dbName_ = $dbName;
    $this->user_ = $user;
    $this->passwd_ = $passwd;
  }

  /**
   * @deprecated
   */
  public function getNs():string {
    return $this->dbName_.".".$this->col_;
  }

  /**
   * @deprecated
   */
  public function getCol():string {
    return $this->col_;
  }

  /**
   * @deprecated
   */
  public function getDB():string {
    return $this->dbName_;
  }

  public function getNamespace():string {
    return $this->dbName_.".".$this->col_;
  }

  public function getCollection():string {
    return $this->col_;
  }

  public function getDBName():string {
    return $this->dbName_;
  }

  public function getManager():Manager {

    if ($this->manager_ === null) {
      if ($this->passwd_ !== null && $this->user_ !== null) {
        $this->manager_ = new Manager($this->addr_
          , ['password'=>$this->passwd_, 'username'=>$this->user_]);
      } else {
        $this->manager_ = new Manager($this->addr_);
      }
    }
    return $this->manager_;
  }

  private $manager_;
  private $dbName_;
  private $col_;
  private $addr_;
  private $user_;
  private $passwd_;
}
