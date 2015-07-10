#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

class  MySeq{
public:
	int start;
	int end;
	int leng;
	int *seq;

	MySeq(int leng)
	{
		this->leng = leng;
		start = 0;
		end = 0;
		seq = (int *)malloc(sizeof (int)* leng);
	}
	void freeSeq()
	{
		free(seq);
	}
	//del
	void ToolSeqInsert(int numberOfNode)
	{//入队
		seq[end] = numberOfNode;
		end = (end + 1) % leng;//
	}
	int  ToolSeqOut()
	{//出队
		int temp = seq[start];
		start = (start + 1) % leng;//
		return temp;
	}
	bool IsSeqEmpty()
	{
		if (start == end)
			return true;
		else
			return false;
	}
};
