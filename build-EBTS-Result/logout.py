# encoding: utf-8
import sys
import re
fin = open('test_meme.txt')
fout = open('log_meme.txt','w')
while 1:
	line = fin.readline()
	if not line:
		break
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
			fout.write('父进程PID编号：'+result4 +'\n' )
		match_v = re.search('For counts of detected and suppressed errors, rerun with: -v',line)
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


#=============Heap summary=============================


		match5 = re.search(r'HEAP SUMMARY',line)
		if match5:
			fout.write('堆内存使用情况统计：\n')

		flag6 = re.search(r'in use at exit: ',line)
		if flag6:
			bytes= re.search(r'(?<=in use at exit: )\d+',line)
			blocks = re.search(r'(?<= bytes in )\d+',line)
			fout.write('退出时仍在使用的堆内存：'+blocks.group()+'块中'+bytes.group()+'字节\n')

		flag7 = re.findall(r'total heap usage:',line)
		if flag7:
			alloc = re.search(r'\d+(?= allocs)',line)
			alloc_result = alloc.group()
			free = re.search(r'\d+(?= frees)',line)
			free_result = free.group()
			allocated = re.search(r'\d+(?= bytes allocated)',line)
			allocated_result = allocated.group()
			fout.write('堆内存总体使用情况:分配了'+alloc_result+'个堆,释放了'+free_result+'个堆,'+allocated_result+'字节被分配过\n\n')


		match9 = re.search(r'LEAK SUMMARY',line)


#============Leak summary================================
		if match9:
			fout.write('内存泄漏情况统计：\n')

		flag10 = re.search(r'definitely lost: ',line)
		if flag10:
			defbytes =  re.search(r'(?<=definitely lost: )\d+',line)
			defblocks = re.search(r'(?<=bytes in )\d+',line)
			fout.write('确定的内存泄漏：'+defblocks.group()+'块中'+defbytes.group()+'字节\n')

		flag11 = re.search(r'indirectly lost: ',line)
		if flag11:
			indbytes =  re.search(r'(?<=indirectly lost: )\d+',line)
			indblocks = re.search(r'(?<=bytes in )\d+',line)
			fout.write('间接的内存泄漏：'+indblocks.group()+'块中'+indbytes.group()+'字节\n')
		flag12 = re.search(r'possibly lost: ',line)
		if flag12:
			posbytes =  re.search(r'(?<=possibly lost: )\d+',line)
			posblocks = re.search(r'(?<=bytes in )\d+',line)
			fout.write('可能的内存泄漏：'+posblocks.group()+'块中'+posbytes.group()+'字节\n')
		flag13 = re.search(r'still reachable: ',line)
		if flag13:
			stibytes =  re.search(r'(?<=still reachable: )\d+',line)
			stiblocks = re.search(r'(?<=bytes in )\d+',line)
			fout.write('仍能到达的内存：'+stiblocks.group()+'块中'+stibytes.group()+'字节\n')
		flag14 = re.search(r'\s\s\s\s\s\s\s\ssuppressed: ',line)
		if flag14:
			supbytes =  re.search(r'(?<=suppressed: )\d+ ',line)
			supblocks = re.search(r'(?<=bytes in )\d+',line)
			fout.write('被阻止的内存：'+supblocks.group()+'块中'+supbytes.group()+'字节\n')

#==============Invalid write or read memory=================================
		match15 = re.search(r'(Invalid write of size)',line)
		if match15:
			invalid_write = re.search(r'(?<=Invalid write of size )\d+',line)
			fout.write('非法写内存大小为：'+invalid_write.group()+'\n')
		match16= re.search(r'(Invalid read of size)',line)
		if match16:
			invalid_read = re.search(r'(?<=Invalid read of size )\d+',line)
			fout.write('非法读内存大小为：'+invalid_read.group()+'\n')
		match17 = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',line)
		if match17:
			called_pos = match17.group()
			fout.write('发生位置为'+called_pos+'\n')
		match18 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',line)
		if match18:
			call_pos = match18.group()
			fout.write('被调用位置为 '+call_pos+'\n')
		# if match17:
		# 	address = match17.group()
		# 	fun_match = re.search(r'(?<=: )\S+',line)
		# 	function = fun_match.group()
		# 	rout_match = re.search(r'(?<=\(in ).+?(?=\))',line)
		# 	#rout = rout_match.group()
		# 	if rout_match:
		# 		rout = rout_match.group()
		# 	fout.write('发生在物理地址'+address+'中：函数'+function+'(该函数在文件 '+rout+')\n')


		match18 = re.search(r'(?<=Address )\b0x[0-9a-fA-F]*?\b',line)
		if match18:
			mem_add = match18.group()
			#after
			mem_afterb = re.search(r'\d+(?= bytes after a block)',line)
			mem_afters = re.search(r'\d+(?<= bytes after a block of size \d)',line)
			if mem_afterb:
				mem_bytes = mem_afterb.group()
				mem_size = mem_afters.group()
				flag_alloc = re.search(r'alloc\'d|new\'d',line)
				flag_free = re.search(r'free\'d|flag_delete',line)
				if flag_alloc:
					fout.write('非法地址为'+mem_add+'是在大小为'+mem_size+'的块分配后的'+mem_bytes+'字节\n')
				if flag_free:
					fout.write('非法地址为'+mem_add+'是在大小为'+mem_size+'的块释放后的'+mem_bytes+'字节\n')
			#before
			mem_beforeb = re.search(r'\d+(?= bytes before a block)',line)
			mem_befores = re.search(r'\d+(?<= bytes before a block of size \d)',line)
			if mem_beforeb:
				mem_bytes = mem_beforeb.group()
				mem_size = mem_beforeb.group()
				flag_alloc2 = re.search(r'alloc\'d|new\'d',line)
				flag_free2 = re.search(r'free\'d|flag_delete',line)
				if flag_alloc2:
					fout.write('非法地址为'+mem_add+'是在大小为'+mem_size+'的块分配前的'+mem_bytes+'字节\n')
				if flag_free2:
					fout.write('非法地址为'+mem_add+'是在大小为'+mem_size+'的块释放前的'+mem_bytes+'字节\n')

			#inside
			mem_insideb = re.search(r'\d+(?= bytes inside a block)',line)
			mem_insides = re.search(r'\d+(?<= bytes inside a block of size \d)',line)
			if mem_insideb:
				mem_bytes = mem_insideb.group()
				mem_size = mem_insides.group()
				flag_alloc3 = re.search(r'alloc\'d|new\'d',line)
				flag_free3 = re.search(r'free\'d|flag_delete',line)
				if flag_alloc3:
					fout.write('非法地址为'+mem_add+'是在大小为'+mem_size+'的块分配内的'+mem_bytes+'字节\n')
				if flag_free3:
					fout.write('非法地址为'+mem_add+'是在大小为'+mem_size+'的块释放内的'+mem_bytes+'字节\n')
#==============Use of uninitialised values========================

		match_uninit = re.search(r'Conditional jump or move depends on uninitialised value',line)
		if match_uninit:
			fout.write('基于未初始化值的的条件跳转或者赋值\n')
		match_uninit_value = re.search(r'Use of uninitialised value of size',line)
		if match_uninit_value:
			uninit_value = re.search(r'(?<=Use of uninitialised value of size )\d+',line).group()
			fout.write('使用未初始化值的大小为:'+uninit_value+'字节\n')

#==============Illegal frees=============================

		match_Invalid_free = re.search(r'Invalid free\(\)',line)
		if match_Invalid_free:
			fout.write('非法释放:\n')

		#miss match:malloc->free new->delete
		match_mismatch = re.search(r'Mismatched free\(\) \/ delete \/ delete',line)
		if match_mismatch:
			fout.write('对已分配内存进行不正确释放(请区分free/delete/delete[])\n')

		#Overlapping source and destination blocks
		match_overlap = re.search(r'Source and destination overlap in',line)
		if match_overlap:
			overlap_type = re.search(r'(?<=Source and destination overlap in ).+(?=\()',line).group()
			overlap = re.search(r'(?<=\().+(?=\))',line).group()
			fout.write('在'+overlap_type+'('+overlap+')中源地址与目标地址重复\n')

#=============Integer Overflow===========================
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
				result_badmalloc = match_badmalloc.group()
				fout.writelines('错误的malloc函数内存分配申请，大小为: '+result_badmalloc)
			match_builtin = re.search(r'(?<= XXX EVIL __builtin_new arg )\d',line)
			if match_builtin:
				result_builtin = match_builtin.group()
				fout.writelines('错误的内建申请，大小为：'+result_builtin)
			match_builtin_vec = re.search(r'(?<=XXX EVIL __builtin_vec_new arg )\d',line)
			if match_builtin_vec:
				result_builtin_vec = match_builtin_vec.group()
				fout.writelines('错误的内建容器申请，大小为：'+result_builtin_vec)		
			match_memalign = re.search(r'(?<=XXX EVIL memalign args )\d',line)
			if match_memalign:
				result_memalign = match_memalign.group()
				fout.writelines('错误的memalign函数分配内存申请，大小为：'+result_memalign)
			match_calloc = re.search(r'(?<=XXX EVIL calloc args )\d',line)
			if match_calloc:
				result_calloc = match_calloc.group()
				fout.writelines('错误的calloc函数分配内存申请，大小为：'+result_calloc)		
			match_realloc = re.search(r'(?<=XXX EVIL realloc arg )\d',line)
			if match_realloc:
				result_realloc = match_realloc.group()
				fout.writelines('错误的realloc函数分配内存申请，大小为：'+result_realloc)

			#free
			match_free = re.search(r'(?<=XXX FREE )\d+',line)
			if match_free:
				result_free = match_free.group()
				fout.writelines('成功释放内存：'+result_free)




			



fin.close()
fout.close()




		
