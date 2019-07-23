<?php declare(strict_types=1);


namespace Tiny\CLI;


class Option {
  private $opt_ = [];

  static public function New() {
    return new Option();
  }

  public function add(string $key, string $help, bool $hasValue):self {
    if (strlen($key) == 1) {
      $key = "-".$key;
    } else if (strlen($key) >= 2) {
      $key = "--".$key;
    }

    $this->opt_[$key] = [$help, $hasValue];

    return $this;
  }

  public function helpStr():string {
    $ret = "";
    foreach ($this->opt_ as $key => $value) {
      $ret .= " $key";
      if ($value[1]) {
        $ret .= " <value>";
      }
    }
    $ret .= PHP_EOL;

    foreach ($this->opt_ as $key => $value) {
      $ret .= "  $key: " . $value[0] . PHP_EOL;
    }

    return $ret;
  }

  public function parse(array $argv):array {
    $ret = [];

    $lastKey = null;

    foreach ($argv as $item) {
      if ($lastKey !== null) {
        $ret[$lastKey] = $item;
        $lastKey = null;
        continue;
      }

      $key = @$this->opt_[$item];
      if ($key === null) {
        throw new \Error($item
          . " 不是一个合法的选项，使用-h查看帮助，注意：需要值的选项必须传值");
      }
      $start = strlen($item) == 2 ? 1 : 2;
      $item = substr($item, $start);

      if ($key[1]) {
        $lastKey = $item;
        continue;
      }

      $ret[$item] = true;
    }

    if ($lastKey !== null) {
      throw new \Error("$lastKey 必须设值");
    }

    return $ret;
  }
}