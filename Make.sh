#!/bin/sh

set -x

cd /home/skye/MyCode/MyFirstProject/build/
cmake -Wformat=0 ../ 
make 
