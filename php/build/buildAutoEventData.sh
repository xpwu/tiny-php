#!/bin/bash

set -e

basepath=$(cd `dirname $0`; pwd)

phpinte -l $basepath
php $basepath/AutoEventDataBuilder.php 

