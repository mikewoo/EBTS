valgrind --log-file=test_meme.txt --tool=memcheck ~/test_meme
valgrind --log-file=test_sc.txt --tool=sconvcheck ~/test_sc
valgrind --log-file=overlog.txt --tool=cojac ~/test_sc 
