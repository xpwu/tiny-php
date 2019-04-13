<?php


namespace Tiny\Logger;


class Config implements \Tiny\Annotation\Config {

  function getHelp(): string {
    return "配置Tiny Logger使用的log类，默认为Log4php，\n"
      . "如果使用此配置，需要使用方在依赖中加入Log4php的三方库，\n"
      . "目前支持使用Log4php的2.0版本";
  }

  const logger = "Tiny\Logger\Log4php";
}