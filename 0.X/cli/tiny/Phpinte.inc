<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2018/1/2
 * Time: 上午2:21
 */

namespace Tiny;


class Phpinte {
  static public function getAllClass():array {
    // phpinte 集成工具生成的中间文件
    return array_keys(\inte_AutoLoader::$classMap_);
  }
}