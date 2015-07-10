#-*-encoding:utf-8-*-
import os,sys
dir = "/home/flight/test/test2/test3/input"
filenum = 0
list = os.listdir(dir)#列出目录下的所有文件和目录
for line in list:
	if os.path:  # 如果是文件就进行处理
		filenum = filenum+1
		num = str(filenum)
		arg = "valgrind  --log-file=./output/log"+num+ ".txt --tool=memcheck /home/flight/test/test2/test3/test_meme<"+dir+"/"+line
		print arg
		os.system(arg)


