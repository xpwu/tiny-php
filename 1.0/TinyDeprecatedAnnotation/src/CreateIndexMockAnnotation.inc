<?php


namespace Tiny\Deprecated\Annotation;


use Tiny\DB\CreateIndexInterface;

class CreateIndexMockAnnotation implements CreateIndexInterface {

  static public function createIndex() {
  }
}