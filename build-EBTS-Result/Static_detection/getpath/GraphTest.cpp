#include <iostream>
#include <fstream>
#include <string>
#include<vector>
using namespace std;

const int MAX_N = 500;              // ×î¶àµÄœÚµãÊýÄ¿
const char* INPUT_FILE = "matrix.txt";
const char* INPUT_NODE = "GraphNode.txt";
const char * FELENODENAME = "string.txt";

vector<string> nodeNameV;

void getNodeName(const char * filename, vector<string> &nodeNameV1)
{
	ifstream ife(filename);
 	//cout << "read file " << endl;
	string temp;
	while (ife >> temp)
	{
		if (temp != "" && temp != " ")
		{
			nodeNameV1.push_back(temp);
		// 	cout << " read  " << temp;
		}
		// else cout << " read  null  ";
	}

}

struct Graph {
    int NodeCount;                  // œÚµãµÄÊýÄ¿
    int AdjMatrix[MAX_N][MAX_N];    // ÁÚœÓŸØÕó,Èç¹ûÍŒÖÐi,jÏàÁÚÔòG[i][j]>0£¬·ñÔòG[i][j]=0
};

typedef int Path[MAX_N];            // ÓÃÀŽŽæŽ¢Â·Ÿ¶
    
typedef bool Mark[MAX_N];           // ±êŒÇ·ÃÎÊ¹ýµÄœÚµã

int paths = 0;						// ŒÇÂŒÉú³ÉµÄÂ·Ÿ¶µÄÊýÄ¿

// ŽòÓ¡Â·Ÿ¶
void PrintPath(Path& path, int length) {        
    for (int i = 0; i < length; i++) {
        if (i != length-1) {
			cout << nodeNameV[path[i]] << "->";
		}
		else {
			cout << nodeNameV[path[i]];
		}
    }
    cout << endl;
	paths = paths + 1;
}

// Éî¶ÈÓÅÏÈËÑË÷
// G ÊäÈëµÄÍŒ£¬
// pathÓÃÀŽŒÇÂŒÂ·Ÿ¶
// visited ÓÃÀŽ±êŒÇËÑË÷¹ýµÄœÚµã£¬³õÊŒ»¯È«²¿Îªfalse
// v µ±Ç°µÄœÚµã
// des Ä¿µÄœÚµã
// length Ä¿Ç°ÒÑŸ­µÃµœµÄÂ·Ÿ¶µÄ³€¶È
void SearchAllPath(const Graph& G, Path& path, Mark& visited, int v, int des, int length) {
    if (visited[v]) return;
    path[length-1] = v;
    if (v == des) {
        PrintPath(path, length);
    } else {
        visited[v] = true;
        for (int i = 0; i < G.NodeCount; i++) 
            if (G.AdjMatrix[v][i] != 0 && !visited[i]) {                
                SearchAllPath(G, path, visited, i, des, length+1);
            }
        visited[v] = false;
    }
}

// ÀûÓÃÉî¶ÈÓÅÏÈËÑË÷²éÕÒÈ«Â·Ÿ¶
// G ÊäÈëµÄÍŒ£¬
// pathÓÃÀŽŒÇÂŒÂ·Ÿ¶
// visited ÓÃÀŽ±êŒÇËÑË÷¹ýµÄœÚµã£¬³õÊŒ»¯È«²¿Îªfalse
// src ÆðÊŒœÚµã
// des Ä¿µÄœÚµã
// length Ä¿Ç°ÒÑŸ­µÃµœµÄÂ·Ÿ¶µÄ³€¶È
void DoDFSSearch(const Graph& G, Path& path, Mark& visited, int src, int des, int length) {
	ifstream finode(INPUT_NODE);
	while (!finode.eof()) {		// Ñ­»·¶ÁÈëÆðÊŒœÚµãºÍ¶ÔÓŠµÄÄ¿µÄœÚµã
		finode >> src >> des;
		SearchAllPath(G, path, visited, src, des, 1);	// œøÐÐÉî¶ÈÓÅÏÈ±éÀú
	}
}

void ReadData(Graph& G)  // ¶ÁÈëÊýŸÝ
{
    ifstream fin(INPUT_FILE);
    fin >> G.NodeCount;       // ¶ÁÈëœÚµãÊýÄ¿£¬œÚµãŽÓ0¿ªÊŒ±êºÅ
    for (int i = 0; i < G.NodeCount; i++) 
        for (int j = 0; j < G.NodeCount; j++) {
            fin >> G.AdjMatrix[i][j];
        }
}

int main()
{
    
    Graph G;
    int src=0, des=0;           // ÆðµãºÍÖÕµã    
    Path path;              // ŽæŽ¢Â·Ÿ¶
    Mark visited;           // ·ÃÎÊ±êŒÇ
    ReadData(G);  // ¶ÁÈëŽæŽ¢ÍŒµÄœÚµãÊýºÍÁÚœÓŸØÕó
    for (int i = 0; i < G.NodeCount; i++) visited[i] = false;   // ³õÊŒ»¯
	getNodeName(FELENODENAME, nodeNameV);
	DoDFSSearch(G, path, visited, src, des, 1);		// Íš¹ýÉî¶ÈÓÅÏÈ²éÕÒÈ«Â·Ÿ¶  
    cout << "--------------------" << endl;
	cout << "生成的路径总数为:" << paths << endl;
    return 0;
}
