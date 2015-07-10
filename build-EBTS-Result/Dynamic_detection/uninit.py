# encoding: utf-8
import sys
import re
fin = open('test_meme.txt')
fout = open('log_uninit.txt','w')
num=0
for line in fin:
	match1 = re.search(r'^==\d+==',line)
	if match1:

	#if one line have nothing write a none line
		match_none = re.search(r'(^==\d+== $)',line)
		if match_none:
			fout.write('\n')

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
			fout.write('父进程PID编号：'+result4 +'' )
		match_v = re.search('For counts of detected and suppressed errors, rerun with: -v',line)
		'''if match_v:
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
#==============Use of uninitialised values========================

		match_uninit = re.search(r'Conditional jump or move depends on uninitialised value',line)
		if match_uninit:
			num+=1
			fout.write('('+str(num)+')'+'基于未初始化值的的条件跳转或者赋值\n')
			next1 = fin.next()
			addr1 = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next1)
			if addr1:
				called_pos = addr1.group()
				fout.write('\t发生位置为'+called_pos+'\n')
				bynext2 = fin.next()
				byaddr2 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext2)
				if byaddr2:
					call_pos = byaddr2.group()
					fout.write('\t被调用位置为 '+call_pos+'\n')
					bynext3 = fin.next()
					byaddr3 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext3)
					if byaddr3:
						call_pos = byaddr3.group()
						fout.write('\t被调用位置为 '+call_pos+'\n')
		match_uninit_value = re.search(r'Use of uninitialised value of size',line)
		if match_uninit_value:
			num+=1
			uninit_value = re.search(r'(?<=Use of uninitialised value of size )\d+',line).group()
			fout.write('('+str(num)+')'+'使用未初始化值的大小为:'+uninit_value+'字节\n')
			next = fin.next()
			addr = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next)
			if addr:
				called_pos = addr.group()
				fout.write('\t发生位置为'+called_pos+'\n')
				bynext = fin.next()
				byaddr = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext)
				if byaddr:
					call_pos = byaddr.group()
					fout.write('\t被调用位置为 '+call_pos+'\n')
					by2next = fin.next()
					byaddr2 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',by2next)
					if byaddr2:
						call_pos = byaddr2.group()
						fout.write('\t被调用位置为 '+call_pos+'\n')
	




fin.close()
fout.close()




		
