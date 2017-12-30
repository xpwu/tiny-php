#!/bin/bash

set -e

basepath=$(cd `dirname $0`; pwd)

phpinte $1 -l $basepath
php $basepath/AutoEventDataBuilder.php 

