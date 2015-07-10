#!/bin/bash
#
python tracemap.py


filename="tracemap.dot"
set `ls -il $filename`
if [ $6 -gt 15 ];
then
  cp tracemap.dot ./Case_generation/
fi

filename="num_File"
set `ls -il $filename`
if [ $6 -gt 0 ];
then
  cp num_File ./test_report/
fi
dot -Tpng  -Gconcentrate=true -O ./Case_generation/tracemap.dot 

sh changepath.sh

