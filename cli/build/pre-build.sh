#!/bin/bash

set -e

# TODO: need modify 
PHP_SEVER_TOP_PATH="../../php"

basepath=$(cd `dirname $0`; pwd)

if [ ${PHP_SEVER_TOP_PATH:0:1} != '/' ] ;then
	PHP_SEVER_TOP_PATH=$basepath/$PHP_SEVER_TOP_PATH
fi

#$PHP_SEVER_TOP_PATH=$(cd `$PHP_SEVER_TOP_PATH`; pwd)

ln -s $PHP_SEVER_TOP_PATH/module $basepath/../ 2>/dev/null
ln -s $PHP_SEVER_TOP_PATH/db $basepath/../ 2>/dev/null

cd $PHP_SEVER_TOP_PATH/build
./buildAutoEventData.sh
cd - >/dev/null


