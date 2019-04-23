<?php


namespace Tiny\Deprecated\Annotation;


use Inte\Annotation;
use Tiny\AnnotationHelper;
use Tiny\DB\CreateIndexInterface;
use Tiny\DB\Index\Annotation\NeedCreateIndex;
use Tiny\Logger;

abstract class AllOldCreateIndexInterfaceHelper extends AnnotationHelper
  implements Annotation, NeedCreateIndex {

  static function createIndex():void {
    /**
     * 目前情况是 此处不能使用self, 子类调用createIndex方法时，self指向的是子类而不是静态绑定
     * 的 AllOldCreateIndexInterfaceHelper。(static 才应该是后期静态绑定)
     * 所以先用 AllOldCreateIndexInterfaceHelper 直接绑定处理此问题
     */
    $helper = AllOldCreateIndexInterfaceHelper::getHelper();
    if ($helper === null) {
      return;
    }

    /**
     * @var CreateIndexInterface[] $all
     */
    $all = $helper->getAll();

    foreach ($all as $item) {
      try {
        Logger::getInstance()->info("create old index: ".$item);
        $item::createIndex();
      } catch (\Exception $exception){
        Logger::getInstance()->error("create old index error: ".$item, $exception);
      }
    }
  }

  static function description():string {
    return "<所有使用CreateIndexInterface注解的DB, 请尽快替换为新的方式>";
  }

  static function getHelper():?AllOldCreateIndexInterfaceHelper {
    $helper = self::getFullClassName();
    if (!class_exists($helper)) {
      Logger::getInstance()->warn("not old CreateIndexInterface --- ".$helper);
      return null;
    }

    return new $helper();
  }

  /**
   * @return string[]
   */
  abstract protected function getAll():array ;
}