#!/bin/bash
#
sed -i '1d' ./CPU_Output_File
sed -i '6,$d' ./CPU_Output_File
sed -i -r '2 s/stopping/停止/' ./CPU_Output_File
sed -i -r '2 s/sleeping/睡眠/' ./CPU_Output_File
sed -i -r '1 s/top/当前时间/' ./CPU_Output_File
sed -i -r 's/Cpu/处理器/' ./CPU_Output_File

sed -i -r 's/Tasks/任务堆栈总量/' ./CPU_Output_File

sed -i -r '1 s/up/系统运行时间/' ./CPU_Output_File
sed -i -r '1 s/users/当前用户数/' ./CPU_Output_File
sed -i -r '1 s/load average/系统负载/' ./CPU_Output_File

sed -i -r '2 s/running/运行/' ./CPU_Output_File
sed -i -r '2 s/zombie/僵尸进程/' ./CPU_Output_File
sed -i -r '3 s/sy,.*ni,/sy, /' ./CPU_Output_File
sed -i -r '3 s/wa,.*st/wa/' ./CPU_Output_File
sed -i -r '3 s/us/用户空间CPU百分比/' ./CPU_Output_File
sed -i -r '3 s/sy/内核空间CPU百分比/' ./CPU_Output_File
sed -i -r '3 s/id/空闲CPU百分比/' ./CPU_Output_File
sed -i -r '3 s/wa/等待输入输出的CPU百分比/' ./CPU_Output_File
sed -i -r 's/KiB Mem/物理内存使用率/' ./CPU_Output_File
sed -i -r 's/buffers/内核缓存内存量/' ./CPU_Output_File

sed -i -r 's/KiB Swap/交换内存使用率/' ./CPU_Output_File

sed -i -r 's/total/总量/g' ./CPU_Output_File
sed -i -r 's/used/已用/g' ./CPU_Output_File
sed -i -r 's/free/空闲/g' ./CPU_Output_File
sed -i -r 's/cached/交换区缓冲内存量/' ./CPU_Output_File

sed -i -r 's/交换内存使用率:/交换内存使用率:/' ./CPU_Output_File

sed -i -r 's/^[[:space:]]//g' ./CPU_Output_File

cp ./CPU_Output_File Tr_CPU_Output_File
sed -i /^[[:space:]]*$/d  ./Tr_CPU_Output_File
sed -i /^$/d ./Tr_CPU_Output_File


 
