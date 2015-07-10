# encoding: utf-8
import sys
import re
fin = open('test_meme.txt')
fout = open('log_leak.txt','w')
num=0
while 1:
	line = fin.readline()
	if not line:
		break
	match1 = re.search(r'^==\d+==',line)
	if match1:

	#if one line have nothing write a none line
	#	match_none = re.search(r'(^==\d+== $)',line)
	#	if match_none:
	#		fout.write('\n')

#==============basic information========================
		match2 = re.search(r'Memcheck',line)
		if match2:
			fout.write('memcheck内存检测工具\n')

		match3 = re.search(r'(?<=Command: ).+',line)
		if match3:
			result3 = match3.group()
			fout.write('操作执行命令：'+result3 +'\n' )

		match4 = re.search(r'(?<=Parent PID: ).+',line)
		if match4:
			result4 = match4.group()
			fout.write('父进程PID编号：'+result4 +'\n' )
		'''match_v = re.search('For counts of detected and suppressed errors, rerun with: -v',line)
		if match_v:
			fout.write('计算检测和阻止的错误数，使用-v命令再次运行\n')
		match_origins = re.search('Use --track-origins=yes to see where uninitialised values come from',line)
		if match_origins:
			fout.write('使用 --track-origins=yes命令查看未初始化值来源\n')
		match_leak = re.search('Rerun with --leak-check=full to see details of leaked memory',line)
		if match_leak:
			fout.write('重新运行--leak-check=full命令查看更多内存泄漏信息\n')
		match_ERROR = re.search(r'(?<=ERROR SUMMARY: )\d+',line)
		if match_ERROR:
			error_sum = match_ERROR.group()
			error_context = re.search(r'\d+(?= contexts)',line).group()
			suppressed_before = re.search(r'(?<=suppressed: )\d+',line).group()
			suppressed_after = re.search(r'\d+(?=\))',line).group()
			fout.write('错误统计：'+error_context+'处中'+error_sum+'个错误(从'+suppressed_after+'中阻止了'+suppressed_before+'个)\n')
'''

#=============Heap summary=============================


		match5 = re.search(r'HEAP SUMMARY',line)
		if match5:
			num+=1
			fout.write('('+str(num)+')'+'堆内存使用情况统计：\n')

		flag6 = re.search(r'in use at exit: ',line)
		if flag6:
			bytes= re.search(r'(?<=in use at exit: )\d+',line)
			blocks = re.search(r'(?<= bytes in )\d+',line)
			fout.write('\t退出时仍在使用的堆内存：'+blocks.group()+'块中'+bytes.group()+'字节\n')

		flag7 = re.findall(r'total heap usage:',line)
		if flag7:
			alloc = re.search(r'\d+(?= allocs)',line)
			alloc_result = alloc.group()
			free = re.search(r'\d+(?= frees)',line)
			free_result = free.group()
			allocated = re.search(r'\d+(?= bytes allocated)',line)
			allocated_result = allocated.group()
			fout.write('\t堆内存总体使用情况:分配了'+alloc_result+'个堆,释放了'+free_result+'个堆,'+allocated_result+'字节被分配过\n')


		match9 = re.search(r'LEAK SUMMARY',line)

		num+=1
#============Leak summary================================
		if match9:
			fout.write('('+str(num)+')'+'内存泄漏情况统计：\n')

		flag10 = re.search(r'definitely lost: ',line)
		if flag10:
			defbytes =  re.search(r'(?<=definitely lost: )\d+',line)
			defblocks = re.search(r'(?<=bytes in )\d+',line)
			fout.write('\t确定的内存泄漏：'+defblocks.group()+'块中'+defbytes.group()+'字节\n')

		flag11 = re.search(r'indirectly lost: ',line)
		if flag11:
			indbytes =  re.search(r'(?<=indirectly lost: )\d+',line)
			indblocks = re.search(r'(?<=bytes in )\d+',line)
			fout.write('\t间接的内存泄漏：'+indblocks.group()+'块中'+indbytes.group()+'字节\n')
		flag12 = re.search(r'possibly lost: ',line)
		if flag12:
			posbytes =  re.search(r'(?<=possibly lost: )\d+',line)
			posblocks = re.search(r'(?<=bytes in )\d+',line)
			fout.write('\t可能的内存泄漏：'+posblocks.group()+'块中'+posbytes.group()+'字节\n')
		flag13 = re.search(r'still reachable: ',line)
		if flag13:
			stibytes =  re.search(r'(?<=still reachable: )\d+',line)
			stiblocks = re.search(r'(?<=bytes in )\d+',line)
			fout.write('\t仍能到达的内存：'+stiblocks.group()+'块中'+stibytes.group()+'字节\n')
		flag14 = re.search(r'\s\s\s\s\s\s\s\ssuppressed: ',line)
		if flag14:
			supbytes =  re.search(r'(?<=suppressed: )\d+ ',line)
			supblocks = re.search(r'(?<=bytes in )\d+',line)
			fout.write('\t被阻止的内存：'+supblocks.group()+'块中'+supbytes.group()+'字节\n')



fin.close()
fout.close()




		
