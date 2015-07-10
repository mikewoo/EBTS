#!/bin/bash
#

sed -i '1,2d' ./SYSIO_Output_File

./row_to_column.pl SYSIO_Output_File

  sed -i -r '1,$ s/r_await/平均每次读操作的等待时间:/g' ./SYSIO_Output_File.new_File
  sed -i -r '1,$ s/w_await/平均每次写操作的等待时间:/g' ./SYSIO_Output_File.new_File
    sed -i -r '1,$ s/await/平均每次操作的等待时间:/g' ./SYSIO_Output_File.new_File
  sed -i -r '1,$ s/Device:/指标:/g' ./SYSIO_Output_File.new_File
  sed -i -r '1,$ s/mmcblk0/数据项:/g' ./SYSIO_Output_File.new_File
sed -i -r '1,$ s/avgqu\-sz/平均I\/O队列长度:/g' ./SYSIO_Output_File.new_File
sed -i -r '1,$ s/avgrq\-sz/平均每次I\/O的数据大小:/g' ./SYSIO_Output_File.new_File
    sed -i -r '1,$ s/svctm/平均每次I\/O的服务时间:/g' ./SYSIO_Output_File.new_File
     sed -i -r '1,$ s/%util/I\/O操作的百分比:/g' ./SYSIO_Output_File.new_File
  sed -i -r '1,$ s/rsec\/s/每秒读扇区:/g' ./SYSIO_Output_File.new_File
  sed -i -r '1,$ s/wsec\/s/每秒写扇区:/g' ./SYSIO_Output_File.new_File
  sed -i -r '1,$ s/wrqm\/s/每秒进行写的次数:/g' ./SYSIO_Output_File.new_File
  sed -i -r '1,$ s/rrqm\/s/每秒进行读的次数:/g' ./SYSIO_Output_File.new_File
     sed -i -r '1,$ s/r\/s/每秒完成读的次数:/g' ./SYSIO_Output_File.new_File
     sed -i -r '1,$ s/w\/s/每秒完成读写的次数:/g' ./SYSIO_Output_File.new_File
   sed -i -r '1,$ s/rkB\/s/每秒读K字节的次数:/g' ./SYSIO_Output_File.new_File
   sed -i -r '1,$ s/wkB\/s/每秒写K字节的次数:/g' ./SYSIO_Output_File.new_File

cp ./SYSIO_Output_File.new_File Tr_SYSIO_Output_File
#sed -i '1d' ./Tr_SYSIO_Output_File
sed -i /^[[:space:]]*$/d  ./Tr_SYSIO_Output_File
sed -i /^$/d ./Tr_SYSIO_Output_File
 
cp Tr_SYSIO_Output_File ./test_report/

cp Tr_CPU_Output_File ./test_report/