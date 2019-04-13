<?php
/**
 * Created by PhpStorm.
 * User: xpwu
 * Date: 2017/12/31
 * Time: 上午2:54
 */

namespace Tiny;


abstract class JsonAPI extends API {

  protected function beforeRun(Request $request, Response $response): bool {

    if (empty($request->data)) {
      $request->data = new \stdClass();
    } else {
      $request->data = json_decode($request->data);
    }

    if ($request->data === false) {
      $response->httpStatus = HttpStatus::ARGS_FORMAT_ERROR;
      $response->httpStatusMsg = "PHP json_decode(request->data) error";
      return false;
    }
    return true;
  }

  protected function afterRun(Request $request, Response $response) {
    if (!isset($response->data) || $response->data === null) {
      return;
    }

    $response->data = json_encode($response->data);

    if ($response->data === false) {
      unset($response->data);
      $response->httpStatus = HttpStatus::FAILED;
      $response->httpStatusMsg = "PHP json_encode(response->data) error";
    }
  }
}