<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/30
 * Time: 下午2:56
 */

namespace Tiny\DB;

use Inte\Annotation;

/**
 * Interface CreateIndexInterface
 * @deprecated
 */
interface CreateIndexInterface extends Annotation {
  static public function createIndex();
}