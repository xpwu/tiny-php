<?php


namespace Tiny;


use Inte\Annotation;

interface CLIAnnotation extends Annotation {
  /**
   * php cli.phar -l 时，此CLI 显示的帮助信息
   * @return string
   */
  function listInfo():string ;
}