# encoding: utf-8
import sys
import re
import os
import shutil
dir = "./output"
filenum = 0
fbefore = open('log_stack.txt','w')
uninit_before = open('log_leak.txt','w')
leak_before = open('log_uninit.txt','w')
integer = open('log_sc.txt','w')
integer.truncate()
leak_before.truncate()
uninit_before.truncate()
fbefore.truncate()
#初始化一些内存统计相关变量
heap_bytes = 0
heap_blocks = 0
heap_allocs = 0
heap_free = 0
heap_allocated = 0
leak_definite_b = 0
leak_definite_l = 0
leak_indirect_b = 0
leak_indirect_l = 0
leak_possible_b = 0
leak_possible_l = 0
leak_reachable_b = 0
leak_reachable_l = 0
leak_suppressed_b = 0
leak_suppressed_l = 0
case_num = 0

list = os.listdir(dir)#列出目录下的所有文件和目录
for file_line in list:
	filenum = filenum +1
	file_trace = dir +'/'+file_line
	if os.path:  # 如果是文件就进行处理
		fin = open(file_trace)
		fout = open('log_stack.txt','a')
		fout_uninit = open('log_uninit.txt','a')
		fout_int = open('log_sc.txt','a')
		fout_leak = open('log_leak.txt','a')
		for line in fin:
			match1 = re.search(r'^==\d+==',line)
			if match1:
			#if one line have nothing write a none line
				match_none = re.search(r'(^==\d+== $)',line)
				#if match_none:
				#	fout.write('\n')
			#=============Integer overflow=============================================
				match_xx = re.search(r'XXX',line)
				if match_xx:
					match_malloc_new = re.search(r'(?<= XXX MALLOC_NEW_BLOCK tid )\d+',line)
					if match_malloc_new:						
						result_malloc_new = match_malloc_new.group()
						result_base = re.search(r'(?<=base )\d+',line).group()
						result_size = re.search(r'(?<=size )\d+',line)
						fout_int.write('分配新的内存块tid编号为:'+result_malloc_new+',基址为:'+result_base+',大小为:'+result_size+'\n')
					match_badmalloc = re.search(r'(?<=XXX EVIL malloc arg ).+',line)
						#print(match_badmalloc)
					if match_badmalloc:
						result_badmalloc = match_badmalloc.group()
						fout_int.write('错误的malloc函数参数： '+result_badmalloc + '\n')
					match_builtin = re.search(r'(?<= XXX EVIL __builtin_new arg ).+',line)
					if match_builtin:
						result_builtin = match_builtin.group()
						fout_int.write('错误的builtin函数参数：'+result_builtin + '\n')
					match_builtin_vec = re.search(r'(?<=XXX EVIL __builtin_vec_new arg ).+',line)
					if match_builtin_vec:
						result_builtin_vec = match_builtin_vec.group()
						fout_int.write('错误的builtin_vec函数参数：'+result_builtin_vec + '\n')		
					match_memalign = re.search(r'(?<=XXX EVIL memalign args ).+',line)
					if match_memalign:
						result_memalign = match_memalign.group()
						fout_int.write('错误的memalign函数参数：'+result_memalign + '\n')
					match_calloc = re.search(r'(?<=XXX EVIL calloc args ).+',line)
					if match_calloc:
						result_calloc = match_calloc.group()
						fout_int.write('错误的calloc函数参数：'+result_calloc + '\n')		
					match_realloc = re.search(r'(?<=XXX EVIL realloc arg ).+',line)
					if match_realloc:
						result_realloc = match_realloc.group()
						fout_int.write('错误的realloc函数参数：'+result_realloc + '\n')

							#free
					match_free = re.search(r'(?<=XXX FREE )\d+',line)
					if match_free:
						result_free = match_free.group()
						fout_int.write('成功释放内存：'+result_free + '\n')
				match_base = re.search(r'(?<=base ).+',line)
				if match_base :
					result_base2 = re.search(r'(?<=base ).+',line).group()
					fout_int.write('\t错误发生地址为：'+result_base2 + '\n')

				#==============================overflow=======================================
		
				match_over = re.search(r'Cojac: Overflow',line)
				if match_over:
					result_type = re.search(r'(?<=Cojac: Overflow, )\S+',line).group()
					result_addr = re.search(r'(?<=at ).+',line).group()
					fout_int.write("整形溢出，错误类型为： "+ result_type +'\n\t发生位置为: '+result_addr + '\n')


		#==============Invalid write or read memory=================================
	
				match3 = re.search(r'(?<=Command: ).+',line)
				if match3:
					case_num = case_num + 1
					fout.write('****执行用例编号：case_'+str(case_num) +'\n' )
					fout_uninit.write('****执行用例编号：case_'+str(case_num) +'\n' )
					fout_leak.write('****执行用例编号：case_'+str(case_num) +'\n' )
					fout_int.write('****执行用例编号：case_'+str(case_num) +'\n' )
				match15 = re.search(r'(Invalid write of size)',line)
				if match15:
					invalid_write = re.search(r'(?<=Invalid write of size )\d+',line)
					fout.write('*非法写内存大小为：'+invalid_write.group()+'\n')
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
				match16= re.search(r'(Invalid read of size)',line)
				if match16:
					invalid_read = re.search(r'(?<=Invalid read of size )\d+',line)
					fout.write('*非法读内存大小为：'+invalid_read.group()+'\n')
					next1 = fin.next()
					addr1 = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next1)
					if addr1:
						called_pos = addr1.group()
						fout.write('发生位置为'+called_pos+'\n')
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
							fout.write('*非法地址为'+mem_add+'是在大小为'+mem_size+'的块分配后的'+mem_bytes+'字节\n')
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
						if flag_free:
							fout.write('\n*非法地址为'+mem_add+'是在大小为'+mem_size+'的块释放后的'+mem_bytes+'字节\n')
							nexta = fin.next()
							addra = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',nexta)
							if addra:
								called_pos = addra.group()
								fout.write('\t发生位置为'+called_pos+'\n')
								bynextb = fin.next()
								byaddrb = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynextb)
								if byaddrb:
									call_pos = byaddrb.group()
									fout.write('\t被调用位置为 '+call_pos+'\n')
									bynextc = fin.next()
									byaddrc = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynextc)
									if byaddrc:
										call_pos = byaddrc.group()
										fout.write('\t被调用位置为 '+call_pos+'\n')
					#before
					mem_beforeb = re.search(r'\d+(?= bytes before a block)',line)
					mem_befores = re.search(r'\d+(?<= bytes before a block of size \d)',line)
					if mem_beforeb:
						mem_bytes = mem_beforeb.group()
						mem_size = mem_beforeb.group()
						flag_alloc2 = re.search(r'alloc\'d|new\'d',line)
						flag_free2 = re.search(r'free\'d|flag_delete',line)
						if flag_alloc2:
							fout.write('*非法地址为'+mem_add+'是在大小为'+mem_size+'的块分配前的'+mem_bytes+'字节\n')
							next_before = fin.next()
							addr_before = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next_before)
							if addr_before:
								called_pos = addr_before.group()
								fout.write('\t发生位置为'+called_pos+'\n')
								bynext_before = fin.next()
								byaddr_before = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_before)
								if byaddr_before:
									call_pos = byaddr_before.group()
									fout.write('\t被调用位置为 '+call_pos+'\n')
									bynext_before = fin.next()
									byaddr_before = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_before)
									if byaddr_before:
										call_pos = byaddr_before.group()
										fout.write('\t被调用位置为 '+call_pos+'\n')
						if flag_free2:
							fout.write('*非法地址为'+mem_add+'是在大小为'+mem_size+'的块释放前的'+mem_bytes+'字节\n')
							next_before2 = fin.next()
							addr_before2 = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next_before2)
							if addr_before2:
								called_pos = addr_before2.group()
								fout.write('\t发生位置为'+called_pos+'\n')
								bynext_before2 = fin.next()
								byaddr_before2 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_before2)
								if byaddr_before2:
									call_pos = byaddr_before2.group()
									fout.write('\t被调用位置为 '+call_pos+'\n')
									bynext_before2 = fin.next()
									byaddr_before2 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_before2)
									if byaddr_before2:
										call_pos = byaddr_before2.group()
										fout.write('\t被调用位置为 '+call_pos+'\n')

					#inside
					mem_insideb = re.search(r'\d+(?= bytes inside a block)',line)
					mem_insides = re.search(r'\d+(?<= bytes inside a block of size \d)',line)
					if mem_insideb:
						mem_bytes = mem_insideb.group()
						mem_size = mem_insides.group()
						flag_alloc3 = re.search(r'alloc\'d|new\'d',line)
						flag_free3 = re.search(r'free\'d|flag_delete',line)
						if flag_alloc3:
							fout.write('*非法地址为'+mem_add+'是在大小为'+mem_size+'的块分配内的'+mem_bytes+'字节\n')
							next_inside = fin.next()
							addr_inside = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next_inside)
							if addr_inside:
								called_pos = addr_inside.group()
								fout.write('\t发生位置为'+called_pos+'\n')
								bynext_inside = fin.next()
								byaddr_inside = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_inside)
								if byaddr_inside:
									call_pos = byaddr_inside.group()
									fout.write('\t被调用位置为 '+call_pos+'\n')
									bynext_inside = fin.next()
									byaddr_inside = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_inside)
									if byaddr_inside:
										call_pos = byaddr_inside.group()
										fout.write('\t被调用位置为 '+call_pos+'\n')
						if flag_free3:
							fout.write('*非法地址为'+mem_add+'是在大小为'+mem_size+'的块释放内的'+mem_bytes+'字节\n')
							next_inside2 = fin.next()
							addr_inside2 = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next_inside2)
							if addr_inside2:
								called_pos = addr_inside2.group()
								fout.write('\t发生位置为'+called_pos+'\n')
								bynext_inside2 = fin.next()
								byaddr_inside2 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_before2)
								if byaddr_inside2:
									call_pos = byaddr_inside2.group()
									fout.write('\t被调用位置为 '+call_pos+'\n')
									bynext_inside2 = fin.next()
									byaddr_inside2 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_inside2)
									if byaddr_inside2:
										call_pos = byaddr_inside2.group()
										fout.write('\t被调用位置为 '+call_pos+'\n')

		#==============Illegal frees=============================

				match_Invalid_free = re.search(r'Invalid free\(\)',line)
				if match_Invalid_free:
					fout.write('*非法释放:\n')

				#miss match:malloc->free new->delete
				match_mismatch = re.search(r'Mismatched free\(\) \/ delete \/ delete',line)
				if match_mismatch:
					fout.write('*对已分配内存进行不正确释放(请区分free/delete/delete[])\n')
					next_ill = fin.next()
					addr_ill = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next_ill)
					if addr_ill:
						called_pos = addr_ill.group()
						fout.write('\t发生位置为'+called_pos+'\n')
						bynext_ill = fin.next()
						byaddr_ill = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_ill)
						if byaddr_ill:
							call_pos = byaddr_ill.group()
							fout.write('\t被调用位置为 '+call_pos+'\n')
							bynext_ill3 = fin.next()
							byaddr_ill3 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_ill3)
							if byaddr_ill3:
								call_pos = byaddr_ill3.group()
								fout.write('\t被调用位置为 '+call_pos+'\n')

				#Overlapping source and destination blocks
				match_overlap = re.search(r'Source and destination overlap in',line)
				if match_overlap:
					overlap_type = re.search(r'(?<=Source and destination overlap in ).+(?=\()',line).group()
					overlap = re.search(r'(?<=\().+(?=\))',line).group()
					fout.write('*在'+overlap_type+'('+overlap+')中源地址与目标地址重复\n')
					next_inside3 = fin.next()
					addr_inside3 = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next_inside3)
					if addr_inside3:
						called_pos = addr_inside3.group()
						fout.write('\t发生位置为'+called_pos+'\n')
						bynext_inside3 = fin.next()
						byaddr_inside3 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_inside3)
						if byaddr_inside3:
							call_pos = byaddr_inside3.group()
							fout.write('\t被调用位置为 '+call_pos+'\n')
							bynext_inside3 = fin.next()
							byaddr_inside3 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_inside3)
							if byaddr_inside3:
								call_pos = byaddr_inside3.group()
								fout.write('\t被调用位置为 '+call_pos+'\n')

		#==============Use of uninitialised values========================
				match_uninit = re.search(r'Conditional jump or move depends on uninitialised value',line)
				if match_uninit:
					fout_uninit.write('*基于未初始化值的的条件跳转或者赋值\n')
					next1 = fin.next()
					addr1 = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next1)
					if addr1:
						called_pos = addr1.group()
						fout_uninit.write('\t发生位置为'+called_pos+'\n')
						bynext2 = fin.next()
						byaddr2 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext2)
						if byaddr2:
							call_pos = byaddr2.group()
							fout_uninit.write('\t被调用位置为 '+call_pos+'\n')
							bynext3 = fin.next()
							byaddr3 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext3)
							if byaddr3:
								call_pos = byaddr3.group()
								fout_uninit.write('\t被调用位置为 '+call_pos+'\n')
				match_uninit_value = re.search(r'Use of uninitialised value of size',line)
				if match_uninit_value:
					uninit_value = re.search(r'(?<=Use of uninitialised value of size )\d+',line).group()
					fout_uninit.write('*使用未初始化值的大小为:'+uninit_value+'字节\n')
					next = fin.next()
					addr = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next)
					if addr:
						called_pos = addr.group()
						fout_uninit.write('\t发生位置为'+called_pos+'\n')
						bynext = fin.next()
						byaddr = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext)
						if byaddr:
							call_pos = byaddr.group()
							fout_uninit.write('\t被调用位置为 '+call_pos+'\n')
							by2next = fin.next()
							byaddr2 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',by2next)
							if byaddr2:
								call_pos = byaddr2.group()
								fout_uninit.write('\t被调用位置为 '+call_pos+'\n')
	

		#=============Heap summary=============================


				match5 = re.search(r'HEAP SUMMARY',line)
				if match5:
					fout_leak.write('堆内存使用情况统计：\n')
				flag6 = re.search(r'in use at exit: ',line)
				if flag6:
					bytes= re.search(r'(?<=in use at exit: )\d+',line).group()
					heap_bytes = heap_bytes + int(bytes)
					blocks = re.search(r'(?<= bytes in )\d+',line).group()
					heap_blocks = heap_blocks +int(blocks)
					fout_leak.write('退出时仍在使用的堆内存：'+blocks+'块中'+bytes+'字节\n')

				flag7 = re.findall(r'total heap usage:',line)
				if flag7:
					alloc = re.search(r'\d+(?= allocs)',line).group()
					heap_allocs = heap_allocs + int(alloc)
					free = re.search(r'\d+(?= frees)',line).group()
					heap_free = heap_free + int(free)
					allocated = re.search(r'\d+(?= bytes allocated)',line).group()
					heap_allocated = heap_allocated +int(allocated)
					fout_leak.write('堆内存总体使用情况:分配了'+alloc+'个堆,释放了'+free+'个堆,'+allocated+'字节被分配过\n')


				match9 = re.search(r'LEAK SUMMARY',line)


		#============Leak summary================================
				if match9:
					fout_leak.write('内存泄漏情况统计：\n')

				flag10 = re.search(r'definitely lost: ',line)
				if flag10:
					defbytes =  re.search(r'(?<=definitely lost: )\d+',line).group()
					leak_definite_b += int(defbytes)
					defblocks = re.search(r'(?<=bytes in )\d+',line).group()
					leak_definite_l += int(defblocks)
					fout_leak.write('\t确定的内存泄漏：'+defblocks+'块中'+defbytes+'字节\n')

				flag11 = re.search(r'indirectly lost: ',line)
				if flag11:
					indbytes =  re.search(r'(?<=indirectly lost: )\d+',line).group()
					indblocks = re.search(r'(?<=bytes in )\d+',line).group()
					leak_indirect_b +=int(indbytes)
					leak_indirect_l +=int(indblocks)
					fout_leak.write('\t间接的内存泄漏：'+indblocks+'块中'+indbytes+'字节\n')
				flag12 = re.search(r'possibly lost: ',line)
				if flag12:
					posbytes =  re.search(r'(?<=possibly lost: )\d+',line).group()
					posblocks = re.search(r'(?<=bytes in )\d+',line).group()
					leak_possible_b += int(posbytes)
					leak_possible_l +=int(posblocks)
					fout_leak.write('\t可能的内存泄漏：'+posblocks+'块中'+posbytes+'字节\n')
				flag13 = re.search(r'still reachable: ',line)
				if flag13:
					stibytes =  re.search(r'(?<=still reachable: )\d+',line).group()
					stiblocks = re.search(r'(?<=bytes in )\d+',line).group()
					leak_reachable_b += int(stibytes)
					leak_reachable_l += int(stiblocks)
					fout_leak.write('\t仍能到达的内存：'+stiblocks+'块中'+stibytes+'字节\n')
				flag14 = re.search(r'\s\s\s\s\s\s\s\ssuppressed: ',line)
				if flag14:
					supbytes =  re.search(r'(?<=suppressed: )\d+ ',line).group()
					supblocks = re.search(r'(?<=bytes in )\d+',line).group()
					leak_suppressed_b += int(supbytes)
					leak_suppressed_l += int(supblocks)
					fout_leak.write('\t被阻止的内存：'+supblocks+'块中'+supbytes+'字节\n')
#           summary :
			
			


		
fout_leak = open('log_leak.txt','a')
fout_leak.write('总共'+str(filenum) +'个用例:\n')
fout_leak.write('所有用例堆内存使用情况统计：\n')
fout_leak.write('退出时仍在使用的堆内存：'+str(heap_blocks)+'块中'+str(heap_bytes)+'字节\n')
fout_leak.write('堆内存总体使用情况:分配了'+str(heap_allocs)+'个堆,释放了'+str(heap_free)+'个堆,'+str(heap_allocated)+'字节被分配过\n\n')
fout_leak.write('所有用例内存泄漏情况统计：\n')
fout_leak.write('\t确定的内存泄漏：'+str(leak_definite_b)+'块中'+str(leak_definite_l)+'字节\n')				
fout_leak.write('\t间接的内存泄漏：'+str(leak_indirect_b)+'块中'+str(leak_indirect_l)+'字节\n')
fout_leak.write('\t可能的内存泄漏：'+str(leak_possible_b)+'块中'+str(leak_possible_l)+'字节\n')
fout_leak.write('\t仍能到达的内存：'+str(leak_reachable_b)+'块中'+str(leak_possible_l)+'字节\n')
fout_leak.write('\t被阻止的内存：'+str(leak_suppressed_b)+'块中'+str(leak_suppressed_l)+'字节\n')

for f in list:
	filepath = os.path.join(dir,f)
	if os.path.isfile(filepath):
		os.remove(filepath)

fin.close()
fout.close()
fout_uninit.close()
fout_leak.close()
fout_int.close()

