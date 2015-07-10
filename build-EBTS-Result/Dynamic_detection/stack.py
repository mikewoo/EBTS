# encoding: utf-8
import sys
import re
fout = open('log_stack.txt','w')
fout.truncate()
fin = open('test_meme.txt')
num =0 
for line in fin:
	match1 = re.search(r'^==\d+==',line)
	if match1:

	#if one line have nothing write a none line
		match_none = re.search(r'(^==\d+== $)',line)

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

	


#==============Invalid write or read memory=================================
		match15 = re.search(r'(Invalid write of size)',line)
		if match15:
			num +=1
			invalid_write = re.search(r'(?<=Invalid write of size )\d+',line)
			fout.write('('+str(num)+')'+'非法写内存大小为：'+invalid_write.group()+'\n')
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
			num +=1
			invalid_read = re.search(r'(?<=Invalid read of size )\d+',line)
			fout.write('('+str(num)+')'+'非法读内存大小为：'+invalid_read.group()+'\n')
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
					fout.write('\t非法地址为'+mem_add+'是在大小为'+mem_size+'的块分配后的'+mem_bytes+'字节\n')
					next1 = fin.next()
					addr1 = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next1)
					if addr1:
						called_pos = addr1.group()
						fout.write('\t\t发生位置为'+called_pos+'\n')
						bynext2 = fin.next()
						byaddr2 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext2)
						if byaddr2:
							call_pos = byaddr2.group()
							fout.write('\t\t被调用位置为 '+call_pos+'\n')
							bynext3 = fin.next()
							byaddr3 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext3)
							if byaddr3:
								call_pos = byaddr3.group()
								fout.write('\t\t被调用位置为 '+call_pos+'\n')
				if flag_free:
					fout.write('\t非法地址为'+mem_add+'是在大小为'+mem_size+'的块释放后的'+mem_bytes+'字节\n')
					nexta = fin.next()
					addra = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',nexta)
					if addra:
						called_pos = addra.group()
						fout.write('\t\t发生位置为'+called_pos+'\n')
						bynextb = fin.next()
						byaddrb = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynextb)
						if byaddrb:
							call_pos = byaddrb.group()
							fout.write('\t\t被调用位置为 '+call_pos+'\n')
							bynextc = fin.next()
							byaddrc = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynextc)
							if byaddrc:
								call_pos = byaddrc.group()
								fout.write('\t\t被调用位置为 '+call_pos+'\n')
			#before
			mem_beforeb = re.search(r'\d+(?= bytes before a block)',line)
			mem_befores = re.search(r'\d+(?<= bytes before a block of size \d)',line)
			if mem_beforeb:
				mem_bytes = mem_beforeb.group()
				mem_size = mem_beforeb.group()
				flag_alloc2 = re.search(r'alloc\'d|new\'d',line)
				flag_free2 = re.search(r'free\'d|flag_delete',line)
				if flag_alloc2:
					fout.write('\t非法地址为'+mem_add+'是在大小为'+mem_size+'的块分配前的'+mem_bytes+'字节\n')
					next_before = fin.next()
					addr_before = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next_before)
					if addr_before:
						called_pos = addr_before.group()
						fout.write('\t\t发生位置为'+called_pos+'\n')
						bynext_before = fin.next()
						byaddr_before = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_before)
						if byaddr_before:
							call_pos = byaddr_before.group()
							fout.write('\t\t被调用位置为 '+call_pos+'\n')
							bynext_before = fin.next()
							byaddr_before = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_before)
							if byaddr_before:
								call_pos = byaddr_before.group()
								fout.write('\t\t被调用位置为 '+call_pos+'\n')
				if flag_free2:
					fout.write('\t非法地址为'+mem_add+'是在大小为'+mem_size+'的块释放前的'+mem_bytes+'字节\n')
					next_before2 = fin.next()
					addr_before2 = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next_before2)
					if addr_before2:
						called_pos = addr_before2.group()
						fout.write('\t\t发生位置为'+called_pos+'\n')
						bynext_before2 = fin.next()
						byaddr_before2 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_before2)
						if byaddr_before2:
							call_pos = byaddr_before2.group()
							fout.write('\t\t被调用位置为 '+call_pos+'\n')
							bynext_before2 = fin.next()
							byaddr_before2 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_before2)
							if byaddr_before2:
								call_pos = byaddr_before2.group()
								fout.write('\t\t被调用位置为 '+call_pos+'\n')

			#inside
			mem_insideb = re.search(r'\d+(?= bytes inside a block)',line)
			mem_insides = re.search(r'\d+(?<= bytes inside a block of size \d)',line)
			if mem_insideb:
				mem_bytes = mem_insideb.group()
				mem_size = mem_insides.group()
				flag_alloc3 = re.search(r'alloc\'d|new\'d',line)
				flag_free3 = re.search(r'free\'d|flag_delete',line)
				if flag_alloc3:
					fout.write('\t非法地址为'+mem_add+'是在大小为'+mem_size+'的块分配内的'+mem_bytes+'字节\n')
					next_inside = fin.next()
					addr_inside = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next_inside)
					if addr_inside:
						called_pos = addr_inside.group()
						fout.write('\t\t发生位置为'+called_pos+'\n')
						bynext_inside = fin.next()
						byaddr_inside = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_inside)
						if byaddr_inside:
							call_pos = byaddr_inside.group()
							fout.write('\t\t被调用位置为 '+call_pos+'\n')
							bynext_inside = fin.next()
							byaddr_inside = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_inside)
							if byaddr_inside:
								call_pos = byaddr_inside.group()
								fout.write('\t\t被调用位置为 '+call_pos+'\n')
				if flag_free3:
					fout.write('\t非法地址为'+mem_add+'是在大小为'+mem_size+'的块释放内的'+mem_bytes+'字节\n')
					next_inside2 = fin.next()
					addr_inside2 = re.search(r'(?<=at )\b0x[0-9a-fA-F]*?\b.+',next_inside2)
					if addr_inside2:
						called_pos = addr_inside2.group()
						fout.write('\t\t发生位置为'+called_pos+'\n')
						bynext_inside2 = fin.next()
						byaddr_inside2 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_before2)
						if byaddr_inside2:
							call_pos = byaddr_inside2.group()
							fout.write('\t\t被调用位置为 '+call_pos+'\n')
							bynext_inside2 = fin.next()
							byaddr_inside2 = re.search(r'(?<=by )\b0x[0-9a-fA-F]*?\b.+',bynext_inside2)
							if byaddr_inside2:
								call_pos = byaddr_inside2.group()
								fout.write('\t\t被调用位置为 '+call_pos+'\n')

#==============Illegal frees=============================

		match_Invalid_free = re.search(r'Invalid free\(\)',line)
		if match_Invalid_free:
			num+=1
			fout.write(str(num)+'非法释放:\n')

		#miss match:malloc->free new->delete
		match_mismatch = re.search(r'Mismatched free\(\) \/ delete \/ delete',line)
		if match_mismatch:
			num+=1
			fout.write('('+str(num)+')'+'对已分配内存进行不正确释放(请区分free/delete/delete[])\n')
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
			num+=1
			overlap_type = re.search(r'(?<=Source and destination overlap in ).+(?=\()',line).group()
			overlap = re.search(r'(?<=\().+(?=\))',line).group()
			fout.write('('+str(num)+')'+'在'+overlap_type+'('+overlap+')中源地址与目标地址重复\n')
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



			



fin.close()
fout.close()




		
