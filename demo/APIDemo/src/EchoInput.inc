<?php


namespace Demo\API;


use Tiny\API;
use Tiny\Logger;
use Tiny\Request;
use Tiny\Response;

class EchoInput extends API {

  protected function run(Request $request, Response $response) {
    Logger::getInstance()->info(__METHOD__ );
    Logger::getInstance()->info($request->data);
    $response->data = $request->data;
  }
}