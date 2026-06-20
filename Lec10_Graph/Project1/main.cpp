#include "AdjMatGraph.h"
#include <iostream>

using namespace std;

int main() {
	AdjMatGraph g;

	for (int i = 0; i < 4; i++)
		g.insertVertex('A' + i);

	g.insertEdge(1, 0);
	g.insertEdge(0, 3);
	g.insertEdge(1, 2);
	g.insertEdge(1, 3);
	g.insertEdge(2, 3);

	printf("인접 행렬로 표현한 그래프 \n");
	g.display();

	FILE* fp;
	fopen_s(&fp, "../text_out.txt", "w");

	// (..:이 파일보다 한 단계 위 폴더 내의 text_out이라는 txt 파일을 write모드로 열겠다)
	if (fp != NULL) {
		g.display(fp);
		fclose(fp);
	}

	//SrchAMGraph g;				//DFS 탐색기능이 있는 그래프 객체 생성
	//g.load("graph.txt")			// 파일로부터 g를 설정함
	printf("그래프 (graph.txt)\n");
	g.display();					//그래프를 화면에 출력

	printf("DFS ==> ");
	g.resetVisited();				// 모든 정점을 방문하지 않았다고 하고
	g.DFS(0);						// 0번째 정점 A에서 깊이 우선 탐색 시작
	printf("\n");

	WGraph wg;
	wg.load("../graph.txt");
	wg.display();

	WGraphMST mst;

	mst.load("../graph.txt");

	cout << "입력 그래프: graph.txt" << endl;
	mst.display();

	cout << "MST By Kruskal's Algorithm" << endl;
	mst.Kruskal();


	WGraphDijkstra h;
	h.load("graph_sp.txt");
	// printf("Dijkstra의 최단경로 탐색을 위한 그래프: graph_sp.txt\n");
	// g.display();
	printf("Shortest Path By Dijkstra Algorithm\n");
	h.ShortestPath(0);
	h.display();



	return 0;
};