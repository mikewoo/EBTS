#include <iostream>
#include <fstream>
#include "Seq.h"
#include<vector>
#include <string>
using namespace std;


const char* INPUT_FILE = "matrix.txt";
const char* INPUT_NODE = "GraphNode.txt";
const char * FELENODENAME="string.txt";
struct Graph {
	int NodeCount;                  // 节点的数目
	//int AdjMatrix[MAX_N][MAX_N];    // 邻接矩阵,如果图中i,j相邻则G[i][j]>0，否则G[i][j]=0
	int **AdjMatrix;
};

const int MAX_POINT = 10000;
const int MAX_NODE = 500000;
typedef int Path[MAX_POINT];            // 用来存储路径
int paths;						// 记录生成的路径的数目

int src;
int des[MAX_POINT];//标记对应节点是否为起始点，结束点， 起始点为0 ，结束点为1


struct treeNode{
	int nodeNumber;//节点图序号
	int fatherNode;//父节点图序号
	int fatherTreeNode;//父节点 tree序号
};

struct  treeNode *TreeNode;
 vector<string> nodeNameV;

void getNodeName(const char * filename, vector<string> &nodeNameV1)
{
    ifstream ife(filename);
    cout<< "read file "<<endl;
      string temp;
    while(ife >> temp)
    {
         if(temp != "" && temp != " ")
         {
             nodeNameV1.push_back(temp);
             cout<< " read  "<< temp;
         }
         else cout<< " read  null  ";
    }

}

// 打印路径
void PrintPathTest(struct  treeNode *TreeNode , int length) {
	//cout << "\n\n\n\n";
	bool* temp = (bool *)malloc(sizeof(bool)*length);
	for (int i = 0; i < length; i++)
	{
		temp[i] = true;
	}
	for (int j = length-1; j >=0; j--)
	{
		if (temp[j]  )
		{
			temp[j] = false;
            cout << (nodeNameV[TreeNode[j].nodeNumber] ) << "->";
			int tempNF = TreeNode[j].fatherTreeNode;
			while (tempNF != -1)
			{
                cout <<  (nodeNameV [TreeNode[tempNF].nodeNumber]) << "->";
				temp[tempNF] = false;
				tempNF = TreeNode[tempNF].fatherTreeNode;
			}
			cout << "\n";
		}	
	}
}


void PrintIntInStack(vector<string> printIntStack)
{
    vector<string> ::iterator iter;
	for (iter = printIntStack.end(); iter != printIntStack.begin(); 	)
	{
		iter--;
		if (iter == printIntStack.begin())
		{
            cout <<  *iter ;
		}
		else
		{
            cout << *iter;
            cout<< "->";
		}
	}
	cout << endl;
}
// 打印路径
void PrintPath(struct  treeNode *TreeNode, int length) {
	///cout << "\n\n\n\n";
	int numberOfPath=0;
	bool* temp = (bool *)malloc(sizeof(bool)*length);
	for (int i = 0; i < length; i++)
	{
		temp[i] = true;
	}

    vector <string > printIntStack;

	for (int j = length - 1; j >= 0; j--)
	{
		if (temp[j] && des[TreeNode[j].nodeNumber] == 1)
		{//没有输出过， 最后一个点是 F
			numberOfPath++;			
			
			temp[j] = false;
			printIntStack.clear();

            printIntStack.push_back( nodeNameV [TreeNode[j].nodeNumber] );
		//	cout << (char)(TreeNode[j].nodeNumber + 'A') << "->";

			int tempNF = TreeNode[j].fatherTreeNode;
			while (tempNF != -1)
			{
                printIntStack.push_back( nodeNameV[TreeNode[tempNF].nodeNumber]);
			//	cout << (char)(TreeNode[tempNF].nodeNumber + 'A') << "->";
				temp[tempNF] = false;
				tempNF = TreeNode[tempNF].fatherTreeNode;
			}
			PrintIntInStack(printIntStack);

			//cout << "\n";
		}
	}
	cout << "--------------------" << endl;
	cout << "The generated path number is:" << numberOfPath << endl;

	free(temp);
}

 

// 动态分配二维数组存储邻接矩阵
int ** NewMatrix(int nodeCount)
{
	int **Matrix;
	Matrix = new int *[nodeCount];
	for (int i = 0; i < nodeCount; i++)
	{
		Matrix[i] = new int[nodeCount];
		//	Matrix[i][2] = i;
	}
	return Matrix;
}

// 释放动态分配二维数组的内存
void DeleteMatrix(int **Matrix, int nodeCount)
{
	for (int i = 0; i < nodeCount; i++)
	{
		delete[] Matrix[i];
	}
	delete Matrix;
}

void ReadData(Graph& G)  // 读入数据
{
	int k = 0, l = 0;
	int src = 0;
	ifstream fin(INPUT_FILE);
	ofstream infile;
	infile.open(INPUT_NODE);
	fin >> G.NodeCount;       // 读入节点数目，节点从0开始标号
	G.AdjMatrix = NewMatrix(G.NodeCount);
	for (int i = 0; i < G.NodeCount; i++)
	{

		for (int j = 0; j < G.NodeCount; j++) {
			fin >> G.AdjMatrix[i][j];
			//cout << G.AdjMatrix[i][j];
		}
		cout << "\n";
	}
	for (k = 0; k < G.NodeCount; k++) {
		for (l = 0; l < G.NodeCount; l++) {
			if (G.AdjMatrix[k][l] == 0) {
				continue;
			}
			else
				break;
		}
		if (l == G.NodeCount) {
			infile << src << " " <<k << endl;
			//infile.close();
			//cout << k << endl;
			//infile >> k;
		}
	}
	//fin.close();
	//infile.close();

}


void ReadStartAndEndFromFile()
{//没有检测起始点 结束点的冲突
	ifstream finode(INPUT_NODE);
	int i = 0;
	for (i = 0; i < MAX_POINT; i++)
	{
		des[i] = -1;
	}
	int temp;
	while (!finode.eof()) {// 循环读入起始节点和对应的目的节点
		finode >> src >> temp;
		des[temp] = 1;
		des[src] = 0;
		// 进行深度优先遍历
	}
}
bool intequality(int * a, int * b)
{//判断相等
	do 
	{
			if (*a != *b)
			{
				return false;
			}	
			a++; b++;
	} while (*a != -1 && *b != -1);
	if (*a == -1 && *b == -1)
		return true;
	else
	{
		return false;
	}
}
bool IsCircleSt(int * path, int length)
{/* 记录走过的 环到 容器，然后新环比较*/
	vector < int * >  circle;
	int lastNumber = path[length - 1];
	int currentTag=length;//记录遍历中 最新的一个循环点

	bool tagresult=false,tagrun=true;

	for (int i = length - 2; tagrun && i >= 0; i--)
	{
		if ( path[i] == lastNumber)
		{//环
			//复制环
			int * tempCircle = (int *)malloc(sizeof (int)* (length - i+1));
			int k;
			for (k = i; k < currentTag; k++)
			{
				tempCircle[k - i] = path[k];
			}
			tempCircle[k - i] = -1;

			
        /*t	cout << "当前环";
			for (int ti = 0; ti <= k - i; ti++)
			{
				cout << tempCircle[ti]<<" ";
			}
			cout << endl;
            est*/

			currentTag = i+ 1;

			//判断是否是相同的环了
			vector <int *> ::iterator iter;
			for (iter = circle.begin(); iter != circle.end(); iter ++)
			{
				if (intequality(*iter,tempCircle))
				{
					tagresult= true;
					tagrun = false;
				}
			}
			//没有重复的 就要添加
			circle.push_back(tempCircle);			
		}
	}

	vector <int *> ::iterator iter;
	for (iter = circle.begin(); iter != circle.end(); iter++)
	{
		free(*iter);
	}

	return tagresult;
}

bool IsCircle(int Last, struct treeNode * TreeNode)
{
	int LastNodeNumber =  TreeNode[Last].nodeNumber;//路径最后点的图序号
	int n = 0;//记录相同点个数


	int path[MAX_NODE];
	int tempFNode = TreeNode[Last].fatherTreeNode;
	int kPath =1;
	path[0] = LastNodeNumber;
	
	while (tempFNode != -1){
		path[kPath] = TreeNode[tempFNode].nodeNumber;//路径
		kPath++;

		if (TreeNode[tempFNode].nodeNumber == LastNodeNumber)
		{//相同点
			n++;
            if( n >=2)
                return true;
			//if (n % 2 == 0)
			{
				//字符串判断
				bool b= IsCircleSt(path, kPath);
				if ( b)
				{
					return true;
				}
			}
		}
		tempFNode = TreeNode[tempFNode].fatherTreeNode;
	} ;

	return false;
}

void Caculate(Graph G)
{
	TreeNode = (struct treeNode *) malloc(sizeof(struct treeNode) *MAX_NODE);
	TreeNode[0].fatherNode = -1;
	TreeNode[0].fatherTreeNode = -1;
	TreeNode[0].nodeNumber = 0;
	int currentNumberOfTreeNode=1;//当前Tree节点的序号

	//应该是广度优先遍历
	MySeq myseq = MySeq(MAX_POINT);//这个队列可能很长
	myseq.ToolSeqInsert(0);
	
	 do 
	 {
		 int tempN = myseq.ToolSeqOut();//队列当前点的序号
		 for (int i = 0; i < G.NodeCount; i++)
		 {
			 int tempGrapthN = TreeNode[tempN].nodeNumber;
			 if (G.AdjMatrix[tempGrapthN][i] != 0)
			 {//节点可以到达的 子节点
			
			//	 cout << "  " << (char)(tempGrapthN + 'A') << "-->" << (char)(i + 'A') << "  ";
				 TreeNode[currentNumberOfTreeNode].fatherNode = tempGrapthN;//父节点 在图的序号  展示
				 TreeNode[currentNumberOfTreeNode].fatherTreeNode = tempN;//父节点 在TreeNode的序号
				 TreeNode[currentNumberOfTreeNode].nodeNumber = i;//节点值 的序号			 

				 //环判别
				 bool b = IsCircle(currentNumberOfTreeNode, TreeNode);
				 if (b)
				{
					 TreeNode[currentNumberOfTreeNode].fatherNode = -1;//父节点 在图的序号  展示
					 TreeNode[currentNumberOfTreeNode].fatherTreeNode = -1;//父节点 在TreeNode的序号
					 TreeNode[currentNumberOfTreeNode].nodeNumber = -1;//节点值 的序号	
					 continue;
				}
				// IsCircle(currentNumberOfTreeNode, TreeNode);
			//test  PrintPathTest(TreeNode, currentNumberOfTreeNode);
		
				 //入队列
				 myseq.ToolSeqInsert(currentNumberOfTreeNode);
				 currentNumberOfTreeNode++;
			 }
		 }
		

	 } while ( ! myseq.IsSeqEmpty());

	 PrintPath(TreeNode, currentNumberOfTreeNode);

	 myseq.freeSeq();
	 free(TreeNode);



}

int main()
{
	Graph G;


	int src=0, des=0;           // 起点和终点    

 
	ReadData(G);  // 读入存储图的节点数和邻接矩阵
	ReadStartAndEndFromFile();
    getNodeName( FELENODENAME,  nodeNameV);
	Caculate(G);

	DeleteMatrix(G.AdjMatrix, G.NodeCount);			// 释放动态分配的内存

	
	return 0;
}
