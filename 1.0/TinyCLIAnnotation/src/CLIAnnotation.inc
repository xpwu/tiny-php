<?php


namespace Tiny;


interface CLIAnnotation {
  /**
   * php cli.phar -l 时，此CLI 显示的帮助信息
   * @return string
   */
  function listInfo():string ;
}