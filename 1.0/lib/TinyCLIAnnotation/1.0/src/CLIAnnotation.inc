<?php


namespace Tiny;



use Inte\MetaAnnotation\Annotation;
use Inte\MetaAnnotation\Inherited;

interface CLIAnnotation extends Annotation, Inherited {
  /**
   * php cli.phar -l 时，此CLI 显示的帮助信息
   * @return string
   */
  function listInfo():string ;
}