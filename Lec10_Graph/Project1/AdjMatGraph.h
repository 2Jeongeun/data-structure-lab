#pragma once
#define MAX_VTXS 20
#include <stdio.h>
#define INF 9999
#define MAX_HEAP_NODE 100
#include <iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class AdjMatGraph {
protected:
	int size;
	char vertices[MAX_VTXS];
	int adj[MAX_VTXS][MAX_VTXS];
public:
	AdjMatGraph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }
	void setEdge(int i, int j, int val) { adj[i][j] = val; }
	bool isEmpty() { return size == 0; }
	bool isFull() { return size >= MAX_VTXS; }

	//그래프 초기화 => 공백 상태의 그래프
	void reset() {
		size = 0;
		for (int i = 0; i < MAX_VTXS; i++)
			for (int j = 0; j < MAX_VTXS; j++)
				setEdge(i, j, 0);
	}

	//정점 삽입
	void insertVertex(char name) {
		if (!isFull()) vertices[size++] = name;
		else printf("Error: 그래프 정점 개수 초과 \n");
	}

	//간선 삽입 : 무방향 그래프의 경우임. (방향, 가중치 그래프에서는 수정)
	void insertEdge(int u, int v) {
		setEdge(u, v, 1);
		setEdge(v, u, 1); //방향 그래프에서는 삭제됨(<u,v>만 존재)
	}

	//그래프 정보 출력(화면이나 파일에 출력)
	//그래프 정보 출력(화면이나 파일에 출력)
	void display(FILE* fp = stdout) {
		fprintf(fp, "%d\n", size);
		for (int i = 0; i < size; i++) {
			fprintf(fp, "%c", getVertex(i));
			for (int j = 0; j < size; j++)
				fprintf(fp, "%3d", getEdge(i, j));
			fprintf(fp, "\n");
		}
	}

	bool visited[MAX_VTXS];	// 정점의 방문 정보

public:
	void resetVisited() {
		for (int i = 0; i < size; i++)
			visited[i] = false;
	}

	bool isLincked(int u, int v) {
		return getEdge(u, v) != 0;
	}

	void DFS(int v) {
		visited[v] = true;
		printf("%c", getVertex(v));

		for (int w = 0; w < size; w++)
			if (isLincked(v, w) && visited[w] == false)
				DFS(w);
	}
};


class WGraph : public AdjMatGraph {
public:
	void insertEdge(int u, int v, int weight) {
		if (weight > INF) weight = INF;
		setEdge(u, v, weight);
	}
	bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }

	void load(const char* filename) {
		FILE* fp;
		fopen_s(&fp, filename, "r");

		if (fp != NULL) {
			int n;
			fscanf_s(fp, "%d", &n);

			for (int i = 0; i < n; i++) {
				char str[80];
				int val;

				fscanf_s(fp, "%79s", str, (unsigned)sizeof(str));

				insertVertex(str[0]);

				for (int j = 0; j < n; j++) {
					fscanf_s(fp, "%d", &val);
					insertEdge(i, j, val);
				}
			}

			fclose(fp);
		}
	}
};

class VertexSets {
	int parent[MAX_VTXS];
	int nSets;
public:
	VertexSets(int n) : nSets(n) {
		for (int i = 0; i < nSets; i++)
			parent[i] = -1;
	}
	bool isRoot(int i) { return parent[i] < 0; }

	int findSet(int v) {
		while (!isRoot(v))v = parent[v];
		return v;
	}
	void unionSets(int s1, int s2) {
		parent[s1] = s2;
		nSets--;
	}
};

class HeapNode {
private:
	int key;    // 간선의 가중치
	int v1;     // 정점 1
	int v2;     // 정점 2

public:
	HeapNode(int k = 0, int u = 0, int v = 0)
		: key(k), v1(u), v2(v) {
	}

	void setKey(int k, int u, int v) {
		key = k;
		v1 = u;
		v2 = v;
	}

	int getKey() const {
		return key;
	}

	int getV1() const {
		return v1;
	}

	int getV2() const {
		return v2;
	}
};

class MinHeap {
private:
	HeapNode node[MAX_HEAP_NODE];
	int size;

public:
	MinHeap() : size(0) {
	}

	bool isEmpty() const {
		return size == 0;
	}

	bool isFull() const {
		return size >= MAX_HEAP_NODE - 1;
	}

	HeapNode& getParent(int i) {
		return node[i / 2];
	}

	void insert(int key, int u, int v) {
		if (isFull()) {
			cout << "Heap is full." << endl;
			return;
		}

		int i = ++size;

		// 새로 들어온 간선의 가중치가 부모보다 작으면 위로 이동
		while (i != 1 && key < getParent(i).getKey()) {
			node[i] = getParent(i);
			i /= 2;
		}

		node[i].setKey(key, u, v);
	}

	HeapNode remove() {
		if (isEmpty()) {
			cout << "Heap is empty." << endl;
			return HeapNode();
		}

		HeapNode item = node[1];
		HeapNode last = node[size--];

		int parent = 1;
		int child = 2;

		while (child <= size) {
			// 오른쪽 자식이 있고, 오른쪽 자식이 더 작으면 오른쪽 선택
			if (child < size &&
				node[child].getKey() > node[child + 1].getKey()) {
				child++;
			}

			// 마지막 노드가 자식보다 작거나 같으면 제자리
			if (last.getKey() <= node[child].getKey()) {
				break;
			}

			node[parent] = node[child];
			parent = child;
			child *= 2;
		}

		node[parent] = last;

		return item;
	}
};




class WGraphMST : public WGraph {
public:
	void Kruskal() {
		MinHeap heap;

		// 1. 그래프의 모든 간선을 최소힙에 삽입
		// 무방향 그래프이므로 i < j 부분만 확인
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
				if (hasEdge(i, j)) {
					heap.insert(getEdge(i, j), i, j);
				}
			}
		}

		// 2. 처음에는 모든 정점이 각각 독립 집합
		VertexSets set(size);

		int edgeAccepted = 0;
		int totalCost = 0;

		// 3. MST는 정점이 n개일 때 n-1개의 간선을 가짐
		while (edgeAccepted < size - 1) {
			if (heap.isEmpty()) {
				cout << "그래프가 연결되어 있지 않아 MST를 만들 수 없습니다." << endl;
				return;
			}

			// 4. 최소 가중치 간선 선택
			HeapNode e = heap.remove();

			int uset = set.findSet(e.getV1());
			int vset = set.findSet(e.getV2());

			// 5. 두 정점이 서로 다른 집합이면 사이클이 생기지 않음
			if (uset != vset) {
				cout << "간선 추가 : "
					<< getVertex(e.getV1()) << " - "
					<< getVertex(e.getV2())
					<< " (비용:" << e.getKey() << ")" << endl;

				// 6. 두 집합을 합침
				set.unionSets(uset, vset);

				edgeAccepted++;
				totalCost += e.getKey();
			}

			// uset == vset인 경우:
			// 이미 같은 집합에 있으므로 간선을 추가하면 사이클 발생
			// 따라서 선택하지 않고 다음 간선으로 넘어감
		}

		cout << "MST 총 비용 : " << totalCost << endl;
	}




	void Prim(int s) {
		bool selected[MAX_VTXS];
		int dist[MAX_VTXS];
		for (int i = 0; i < size; i++) {
			dist[i] = INF;
			selected[i] = false;
		}
		dist[s] = 0; // 시작 정점
		for (int i = 0; i < size; i++) {
			int u = getMinVertex(selected, dist);
			selected[u] = true;
			if (dist[u] == INF) return;
			printf("%c ", getVertex(u));
			for (int v = 0; v < size; v++)
				if (getEdge(u, v) != INF)
					if (!selected[v] && getEdge(u, v) < dist[v])
						dist[v] = getEdge(u, v);
		}
		printf("\n");
	}

	int getMinVertex(bool* selected, int* dist) {
		int minv = 0;
		int mindist = INF;
		for (int v = 0; v < size; v++)
			if (!selected[v] && dist[v] < mindist) {
				mindist = dist[v];
				minv = v;
			}
		return minv;
	}

};


class WGraphDijkstra : public WGraph {
	int dist[MAX_VTXS]; // 시작노드로부터의 최단경로 거리
	bool found[MAX_VTXS]; // 방문한 정점 표시
public:
	int chooseVertex() {
		int min = INF;
		int minpos = -1;
		for (int i = 0; i < size; i++)
			if (dist[i] < min && !found[i]) {
				min = dist[i];
				minpos = i;
			}
		return minpos;
	}
	void printDistance() { // dist 상태를 출력하는 함수
		for (int i = 0; i < size; i++)
			printf("%5d", dist[i]);
		printf("\n");
	}

	void ShortestPath(int start) {
		for (int i = 0; i < size; i++) {
			dist[i] = getEdge(start, i);
			found[i] = false;
		}
		found[start] = true; // 시작노드 방문 표시
		dist[start] = 0; // 최초 거리
		for (int i = 0; i < size; i++) {
			printf("Step%2d:", i + 1);
			printDistance();
			int u = chooseVertex();
			found[u] = true;
			for (int w = 0; w < size; w++) {
				if (found[w] == false)
					if (dist[u] + getEdge(u, w) < dist[w])
						dist[w] = dist[u] + getEdge(u, w);
			}
		}
	}
};