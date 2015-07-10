#!/bin/bash
#
echo "test" | ./Static_detection/long  > ./Static_detection/Sensitive_Area.txt

cd Static_detection
sed -i /^[[:space:]]*$/d ./Sensitive_Area.txt
sed -i /^$/d ./Sensitive_Area.txt

cp Sensitive_Area.txt ../test_report/