#!/bin/bash
#!/bin/bash
#!/bin/bash
#!/bin/bash
#!/bin/bash
#
cd Case_generation
filename="tracemap.dot_File"
set `ls -il $filename`
if [ $6 -gt 15 ];
then
  cp tracemap.dot get_path_File
fi

#[ -s ../tracemap.dot ] && (cp ../tracemap.dot get_path_File)

sed -i '1d'  ./get_path_File
sed -i '$d' ./get_path_File
sed -i /^[[:space:]]*$/d  ./get_path_File
sed -i /^$/d ./get_path_File
#cat ../num_File >> get_path_File

filename="tracemap.dot.png"
set `ls -il $filename`
if [ $6 -gt 115 ];
then
  cp tracemap.dot.png ../test_report/
fi
[ -s get_path_File ] && (cp get_path_File get_trace_File)

filename="get_trace_File"
set `ls -il $filename`
if [ $6 -gt 25 ];
then
  cp get_trace_File ../test_report/get_trace_File
fi
#[ -s get_trace_File ] && (cp get_trace_File ../test_report/get_trace_File)

filename="testcases_File"
set `ls -il $filename`
if [ $6 -gt 1 ];
then
  cp testcases_File ../test_report/testcases_File
fi

rm -rf /home/gmm/Documents/EBTS/build-EBTS-Result/trace/*
#[ -s testcases_File ] && (cp testcases_File ../test_report/testcases_File)
