<?php


namespace Tiny\Deprecated\Annotation;


use Tiny\AnnotationHelper;
use Tiny\DB\CreateIndexInterface;
use Tiny\DB\Index\Annotation\NeedCreateIndex;
use Tiny\Logger;

abstract class AllOldCreateIndexInterfaceHelper extends AnnotationHelper
  implements NeedCreateIndex {

  static function createIndex():void {
    $helper = self::getHelper();
    if ($helper === null) {
      return;
    }

    /**
     * @var CreateIndexInterface[] $all
     */
    $all = $helper->getAll();

    foreach ($all as $item) {
      try {
        Logger::getInstance()->info("create index: ".$item);
        $item::createIndex();
      } catch (\Exception $exception){
        Logger::getInstance()->error("create index error: ".$item, $exception);
      }
    }
  }

  static function getDBName():string {
    return "<所有使用CreateIndexInterface注解的DB>";
  }

  static function getCollectionName():string {
    return "<请尽快替换为新的方式>";
  }

  static function getHelper():?AllOldCreateIndexInterfaceHelper {
    $helper = self::getFullClassName();
    if (!class_exists($helper)) {
      return null;
    }

    return new $helper();
  }

  /**
   * @return string[]
   */
  abstract protected function getAll():array ;
}