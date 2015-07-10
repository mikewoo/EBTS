# encoding: utf-8
import sys
import re
import os
import glob
import shutil
import string


dir = "./trace"
fp=open('tracemap.dot','w')
fp.truncate()
fp.close()
fp=open("tracemap.dot","a")
fp.write('digraph G{ \n')
#fin = open("/home/flight/tracelog/1.log")
next_addr='START'
next_t_id = '0'
next_bin = 'null' 
filenum =0
list = os.listdir(dir)
for file_line in list:
	filenum = filenum +1
	file_trace = dir +'/'+file_line
	if os.path:  # 如果是文件就进行处理
		fin = open(file_trace)
		fp.write('START')
		for line in fin:
			global block_addr,t_id,compare,value#'','','','','',''
			match_if = re.search(r'^ASSERT\(t_(?P<addr>([0-9a-fA-F]*))_(?P<t_id>[0-9]*)_(?P<count>([0-9]*))=IF (?P<compare>[A-Z]*)\(t_[0-9a-fA-F]*_\d*_\d*\[\d:\d\],0hex(?P<value>\d*)\[\d:\d\]\) THEN 0hex0000000000000001 ELSE 0hex0000000000000000 ENDIF\)\;',line)#*_\d*_\d* : BITVECTOR\(\d*\)\;
			if match_if:	
				#print match.group('addr')
				#print match.group('value')
				block_addr = match_if.group('addr')
				t_id = match_if.group('t_id')		
				count = match_if.group('count')
				compare = match_if.group('compare')
				value = match_if.group('value')
				if value == '0000000000000000':
					value_t = '0'
				else:
					value_t = re.search(r'^0*(?P<num>(\d+))',value).group('num')
				if (compare == 'BVLT') or(compare =='SBVLT'):
					compare_type = '<'
				elif (compare == 'BVGE')or(compare=='SBVGE'):
					compare_type = '>='
				elif compare == 'IFT':
					compare_type = '='
				elif compare == 'IFNOT':
					compare_type = '!='
				elif (compare == 'BVLE')or(compare=='SBVLE'):
					compare_type = '<='
				elif (compare == 'BVGT')or(compare =='SBVGT'):
					compare_type = '>'

				else:
					compare_type = 'unknown type'
				fp.write('->\"'+block_addr+'_'+t_id+'_'+count+compare_type+value_t+'\"')
				#fp.write('->'+block_addr+t_id+count+compare_type+value_t)
				
				
			match_if2 = re.search(r'^ASSERT\(t_(?P<addr>([0-9a-fA-F]*))_(?P<t_id>[0-9]*)_(?P<count>([0-9]*))=IF (?P<compare>[A-Z]*)\(0hex(?P<value>\d*)\, (t_[0-9a-fA-F]*)_(\d*)_(\d*)\) THEN 0bin1 ELSE 0bin0 ENDIF\)\;',line)# 
			if match_if2:	
				#print match_if2.group('addr')
				#print match.group('value')
				block_addr = match_if2.group('addr')
				t_id = match_if2.group('t_id')		
				count = match_if2.group('count')
				compare = match_if2.group('compare')
				value = match_if2.group('value')
				if value == '0000000000000000':
					value_t = '0'
				else:
					value_t = re.search(r'^0*(?P<num>(\d+))',value).group('num')
				if (compare == 'BVLT') or(compare =='SBVLT'):
					compare_type = '<'
				elif (compare == 'BVGE')or(compare=='SBVGE'):
					compare_type = '>='
				elif compare == 'IFT':
					compare_type = '='
				elif compare == 'IFNOT':
					compare_type = '!='
				elif (compare == 'BVLE')or(compare=='SBVLE'):
					compare_type = '<='
				elif (compare == 'BVGT')or(compare =='SBVGT'):
					compare_type = '>'

				else:
					compare_type = 'unknown type'
				fp.write('->\"'+block_addr+'_'+t_id+'_'+count+compare_type+value_t+'\"')
			match_hex = re.search(r'^ASSERT\(t_(?P<addr>([0-9a-fA-F]*))_(?P<t_id>[0-9]*)_(?P<count>([0-9]*))=IF t_[0-9a-fA-F]*_\d*_\d*=0hex(?P<value>([0-9a-fA-F]*)) THEN 0bin1 ELSE 0bin0 ENDIF\)\;',line)#t_[0-9]*)_([0-9]*)_([0-9]*) THEN 0bin[0|1] ELSE 0bin[0|1] ENDIF
			
			if match_hex:
				block_addr = match_hex.group('addr')
				t_id = match_hex.group('t_id')
				count_t = match_hex.group('count')
				value_t = match_hex.group('value') 
				compare_type = '='
				fp.write('->\"'+block_addr+'_'+t_id+'_'+count_t+compare_type+value_t+'\"')
			match_hex2 = re.search(r'^ASSERT\(t_(?P<addr>([0-9a-fA-F]*))_(?P<t_id>[0-9]*)_(?P<count>([0-9]*))=IF NOT\(t_[0-9a-fA-F]*_\d*_\d*=0hex(?P<value>([0-9a-fA-F]*))\) THEN 0bin1 ELSE 0bin0 ENDIF\)\;',line)#t_[0-9]*)_([0-9]*)_([0-9]*) THEN 0bin[0|1] ELSE 0bin[0|1] ENDIF
			if match_hex2:
				block_addr = match_hex2.group('addr')
				t_id = match_hex2.group('t_id')
				count_t = match_hex2.group('count')
				value_t = match_hex2.group('value') 
				'''if string.atoi(match_hex2.group('value'),16) < 65:
					value_t = match_hex2.group('value') 
				else:
					value_t = chr(string.atoi(match_hex2.group('value'),16))'''
				compare_type = '!='
				fp.write('->\"'+block_addr+'_'+t_id+'_'+count_t+compare_type+value_t+'\"')
			'''match_bin  = re.search(r'^ASSERT\(t_(?P<addr_bin>([0-9a-fA-F]*))_(?P<bin_t_id>[0-9]*)_[0-9]*=0bin(?P<bin>[0|1])\)\;$',line)
			if match_bin:
				#print match_bin.group()
				next_addr = match_bin.group('addr_bin')
				next_t_id = match_bin.group('bin_t_id')
				next_bin = match_bin.group('bin')
				#print next_addr	
				#fp.write('->'+'_0bin'+next_bin)
				if next_bin == '1':
					#fp.write('->'+block_addr+'_'+t_id+'_'+count+compare_type+value_t+':true')
					fp.write('->\"'+block_addr+'_'+t_id+'_'+count+compare_type+value_t+':true\"')
				else:
					#fp.write('->'+block_addr+'_'+t_id+'_'+count+compare_type+value_t+':false')
					fp.write('->\"'+block_addr+'_'+t_id+'_'+count+compare_type+value_t+':false\"')'''
		fin.close()
		#fp.write(';')		
		fp.write('->"trace_'+str(filenum)+'_end\";\n')
fs = open('num.txt','w')
if filenum>0:
	fs.write('分支路径的条数为:'+str(filenum))
fs.close()
fp.write('}')
fp.close()

