#!/bin/bash
#

echo "test" | ./lastNoCircle_Matrix
./readToMatrix

./ci > get_path.txt
./ci_Last > get_path.txt
#sed -i /$/d get_path.txt
sed  -i -r 's/--------------------//'  ./get_path.txt
sed -i /^[[:space:]]*$/d  ./get_path.txt
sed -i /^$/d ./get_path.txt
sort -k2n get_path.txt | uniq > get_pathnew.txt
rm get_path.txt
mv get_pathnew.txt get_path.txt
[ -s get_path.txt ] && (cp get_path.txt ../../test_report/)






