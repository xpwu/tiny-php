<?php


namespace Tiny\CLI\Command;


use Tiny\CLI\Annotation\AllCLIAnnotation;
use Tiny\CLI\Command;

class ListCommand implements Command {

  function run() {
    $impl = AllCLIAnnotation::getImpl();
    $annotations = $impl->getAllCLIAnnotation();

    foreach ($annotations as $annotation) {
      echo get_class($annotation) . "\t". $annotation->listInfo() . PHP_EOL;
    }
  }
}