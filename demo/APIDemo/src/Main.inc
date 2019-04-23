<?php


namespace Demo\API;


use Inte\RunTime;

class Main {
  static public function main(){
    $_SERVER["REQUEST_URI"] = "Demo\API\EchoInput";
    require RunTime::default()->getPharDir(). DIRECTORY_SEPARATOR . "operation_config.php";

    \Tiny\API\Main::main();
  }
}