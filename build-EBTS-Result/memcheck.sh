#!/bin/bash
#
cp SYS_time_File ./test_report/
cd Dynamic_detection
python translog.py
cp *_File ../test_report/
cp ../rongYu_File ../test_report/
