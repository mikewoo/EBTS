#!/usr/bin/python
#
f = open("b.txt", 'w')
i=0
for line in  open("SYSIO_Output.txt"):
	i+=1
	if( i%2 ) <> 0:
		#print " first"
		str1 = line
		print str1

	else :
		#print " second "
		str2 = line
		print str2


	#i = i + 1
#str1 = 'adsfa asdfds sdgdsg sdgfsdg sdgsdg'
#str2 = 'sadfds dfsdf sdfdsf sdfsdf dfsdfsd'
str1 = str1.strip('\n')
str2 = str2.strip('\n')
li = str1.split(" ", 14)
fn = str2.split(" ", 14)
for i, j in zip(fn, li):
    print >> f, ('\t%s:\t\t\t%s' % (i, j)).title()
