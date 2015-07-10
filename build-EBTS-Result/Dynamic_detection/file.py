#coding=utf-8

import os
import time
def scan_files(directory,prefix=None,postfix=None):
  files_list=[]
    
  for root, sub_dirs, files in os.walk(directory):
    for special_file in files:
      if postfix:
        if special_file.endswith(postfix):
          files_list.append(special_file)
      elif prefix:
        if special_file.startswith(prefix):
          files_list.append(special_file)
      else:
        files_list.append(special_file)
               
  return files_list

lists = scan_files("/home/gmm/Documents/EBTS/build-EBTS-Result/Dynamic_detection/output/mem/",postfix=".log")
f = open("/home/gmm/Documents/EBTS/build-EBTS-Result/Dynamic_detection/log.log","w")
for l in lists:
	s = '/home/gmm/Documents/EBTS/build-EBTS-Result/Dynamic_detection/output/mem/'+str(l)+'\n'
    	f.write(s)



