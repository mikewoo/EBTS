# encoding: utf-8
import sys
import re
file = open('overlog.txt')
string1 = file.read()[5:len(file.readlines())-1]
#string1 = file.read()[7:]
#string = 's\n' +string+'\nd'
file2 = open('test_sc.txt')
string2 = file2.read()
string ='\n'+ string2+'\n'+str(string1)+'\n'
file3 = open('sc_total.txt','w')
file3.write(string)
file.close()
file2.close()
file3.close()
fin = open('sc_total.txt')
fout = open('log_sc.txt','w')
num=0
while 1:
	line = fin.readline()
	if not line:
		break
	match1 = re.search(r'^==\d+==',line)
	if match1:
#==============basic information========================
		match2 = re.search(r'SconvCheck',line)
		if match2:
			fout.write('sconvcheck整数溢出检测工具\n')
		match3 = re.search(r'(?<=Command: ).+',line)
		if match3:
			result3 = match3.group()
			fout.write('操作执行命令：'+result3 +'\n' )

		match4 = re.search(r'(?<=Parent PID: ).+',line)
		if match4:
			result4 = match4.group()
			fout.write('父进程PID编号：'+result4 +'\n' )
#============================================================
		match_xx = re.search(r'XXX',line)
		if match_xx:
			match_malloc_new = re.search(r'(?<= XXX MALLOC_NEW_BLOCK tid )\d+',line)
			if match_malloc_new:
				result_malloc_new = match_malloc_new.group()
				result_base = re.search(r'(?<=base )\d+',line).group()
				result_size = re.search(r'(?<=size )\d+',line)
				fout.write('分配新的内存块tid编号为:'+result_malloc_new+',基址为:'+result_base+',大小为:'+result_size+'\n')
			match_badmalloc = re.search(r'(?<=XXX EVIL malloc arg ).+',line)
			#print(match_badmalloc)
			if match_badmalloc:
				num+=1
				result_badmalloc = match_badmalloc.group()
				fout.write('('+str(num)+')'+'错误的malloc函数参数： '+result_badmalloc + '\n')
			match_builtin = re.search(r'(?<= XXX EVIL __builtin_new arg ).+',line)
			if match_builtin:
				num+=1
				result_builtin = match_builtin.group()
				fout.write('('+str(num)+')'+'错误的builtin函数参数：'+result_builtin + '\n')
			match_builtin_vec = re.search(r'(?<=XXX EVIL __builtin_vec_new arg ).+',line)
			if match_builtin_vec:
				num+=1
				result_builtin_vec = match_builtin_vec.group()
				fout.write('('+str(num)+')'+'错误的builtin_vec函数参数：'+result_builtin_vec + '\n')		
			match_memalign = re.search(r'(?<=XXX EVIL memalign args ).+',line)
			if match_memalign:
				num+=1
				result_memalign = match_memalign.group()
				fout.write('('+str(num)+')'+'错误的memalign函数参数：'+result_memalign + '\n')
			match_calloc = re.search(r'(?<=XXX EVIL calloc args ).+',line)
			if match_calloc:
				num+=1
				result_calloc = match_calloc.group()
				fout.write('('+str(num)+')'+'错误的calloc函数参数：'+result_calloc + '\n')		
			match_realloc = re.search(r'(?<=XXX EVIL realloc arg ).+',line)
			if match_realloc:
				num+=1
				result_realloc = match_realloc.group()
				fout.write('('+str(num)+')'+'错误的realloc函数参数：'+result_realloc + '\n')

			#free
			match_free = re.search(r'(?<=XXX FREE )\d+',line)
			if match_free:
				result_free = match_free.group()
				fout.write('\t成功释放内存：'+result_free + '\n')
		match_base = re.search(r'(?<=base ).+',line)
		if match_base :
			result_base2 = re.search(r'(?<=base ).+',line).group()
			fout.write('\t错误发生地址为：'+result_base2 + '\n')

#==============================overflow=======================================
		
		match_over = re.search(r'Cojac: Overflow',line)
		if match_over:	
			num+=1
			result_type = re.search(r'(?<=Cojac: Overflow, )\S+',line).group()
			result_addr = re.search(r'(?<=at ).+',line).group()
			fout.write('('+str(num)+')'+"整形溢出，错误类型为： "+ result_type +'\n\t发生位置为: '+result_addr + '\n')
fout.close()
fin.close()






