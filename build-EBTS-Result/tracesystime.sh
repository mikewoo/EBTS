#!/bin/bash
#
#sed -i '1,4d' ./SYS_time.txt
sed -i '1d' ./SYS_time.txt
cp SYS_time.txt ./test_report/