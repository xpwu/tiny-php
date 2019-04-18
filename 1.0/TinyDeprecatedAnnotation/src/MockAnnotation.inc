<?php


namespace Tiny\Deprecated\Annotation;


use Tiny\DB\CreateIndexInterface;

class MockAnnotation implements CreateIndexInterface {

  static public function createIndex() {
  }
}