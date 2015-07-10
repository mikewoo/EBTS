#!/bin/bash
#
cp ./test ./Static_detection/getpath/test
sh executablecode.sh
sh sensitivetest.sh
cp test getpath/
cd ./Static_detection/getpath
sh getpath.sh
sh getgraph.sh
#sh tree.sh
