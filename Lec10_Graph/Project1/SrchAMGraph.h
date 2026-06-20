#pragma once
#define MAX_VTXS 20
#include <stdio.h>

class SrchAMGraph :public AdjMatGraph
{
	bool visited[MAX_VTXS];	// 정점의 방문 정보
public:
	void resetVisited() {	// 모든 정점을 방문하지 않았다고 설정
		for (int i = 0; i < size; i++)
			visited[i] = false;
	}
	bool isLincked(int u, int v) { return getEdge(u, v) != 0; }

	//깊이 우선 탐색 함수
	void DFS(int v) {
		visited[v] = true;				//현재 정점을 방문함
		printf("%c", getVertex(v));		// 정점의 이름 출력

		for (int w = 0; w < size; w++)
			if (isLincked(v, w) && visited[w] == false)
				DFS(w); //연결 + 방문x => 순환호출로 방문
	}
};
