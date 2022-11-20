#include <stdio.h>
#include <stdlib.h>

typedef struct _Vertex {
	int idx;
	int data;
	int marked;
} Vertex;

typedef struct my_graph {
	int** arr;
	Vertex** vert_arr;
	int curr_idx;
	int size;
	
	void (*insertVertex)(struct my_graph*, int);
	void (*insertEdge)(struct my_graph*, Vertex*, Vertex*);
	Vertex* (*get_vertex_by_value)(struct my_graph* self, int value);
	void (*deleteEdge)(struct my_graph* self, Vertex* v1, Vertex* v2);
	void (*deleteVertex)(struct my_graph* self, Vertex* v1);
	Vertex** (*adjacent)(struct my_graph* self, Vertex* v);
	void (*print_DFS)(struct my_graph*, Vertex*);

} Graph;

void insertVertex(Graph*,int) ;
void insertEdge(Graph* self, Vertex* v1, Vertex* v2);
Vertex* get_vertex_by_value(Graph* self, int value);
void deleteEdge(Graph* self, Vertex* v1, Vertex* v2);
void deleteVertex(Graph* self, Vertex* v1);
Vertex** adjacent(Graph* self, Vertex* v);
void print_DFS(struct my_graph*, Vertex*);
// 인접배열 그래프 생성
Graph* create_arr_graph(int size) {

	Graph* graph = malloc(sizeof(Graph));
	graph->arr = malloc(sizeof(int*) * size);

	for (int i = 0; i < size; i++) {
		graph->arr[i] = malloc(sizeof(int) * size);
		memset(graph->arr[i], 0, sizeof(int) * size);
	}

	graph->vert_arr = malloc(sizeof(Vertex*) * size);

	graph->curr_idx = 0;
	graph->size = size;
	graph->insertVertex = insertVertex;
	graph->insertEdge = insertEdge;
	graph->deleteEdge = deleteEdge;
	graph->deleteVertex = deleteVertex;
	graph->adjacent = adjacent;
	graph->get_vertex_by_value = get_vertex_by_value;
	graph->print_DFS = print_DFS;

	return graph;
}
// 정점 생// 정점 생성성
Vertex* get_vertex(int v) {
	Vertex* vert = malloc(sizeof(Vertex));
	vert->data = v;
	vert->marked = 0;
	return vert;
}

// 정점 추가
void insertVertex(Graph* self, int v) {
	Vertex* vert = get_vertex(v);
	vert->idx = self->curr_idx++;
	self->vert_arr[vert->idx] = vert;
}

// 간선 추가
void insertEdge(Graph* self, Vertex* v1, Vertex* v2) {
	// 무방향
	self->arr[v1->idx][v2->idx] = 1;
	self->arr[v2->idx][v1->idx] = 1;
}

void deleteEdge(Graph* self, Vertex* v1, Vertex* v2) {
	self->arr[v1->idx][v2->idx] = 0;
	self->arr[v2->idx][v1->idx] = 0;
}

Vertex** adjacent(Graph* self, Vertex* v) {
	if (v == NULL) {
		return NULL;
	}
	Vertex** adjacent_vert_arr = malloc(sizeof(Vertex*) * (self->size));
	if (adjacent_vert_arr == NULL) {
		return NULL;
	}
	int idx = 0;
	for (int i = 0; i < self->size; i++) {
		if (self->arr[v->idx][i] == 1) {
			adjacent_vert_arr[idx++] = self->vert_arr[i];
		}
	}
	adjacent_vert_arr[idx] = NULL;
	return adjacent_vert_arr;
}

void deleteVertex(Graph* self, Vertex* v1) {
	Vertex** result = adjacent(self, v1);
	for (int i = 0; ; i++) {
		if (result[i] == NULL) {
			return;
		}

		self->deleteEdge(self, v1, result[i]);
	}
}


Vertex* get_vertex_by_value(Graph* self, int value) {
	for (int i = 0; i < self->size; i++) {
		if (self->vert_arr[i]->data == value) {
			return self->vert_arr[i];
		}
	}
	return NULL;
}

void print_DFS(Graph* self, Vertex* std) {
	if (std == NULL) {
		return;
	}
	std->marked = 1;
	printf("%d ", std->data);

	Vertex** rst = self->adjacent(self, std);
	for (int i = 0; ; i++) {
		if (rst[i] == NULL) {
			break;
		}
		if (rst[i]->marked == 0) {
			print_DFS(self, rst[i]);
		}
	};
}
int main(void) {

	Graph* graph = create_arr_graph(10);
	
	for (int i = 1; i <= 6; i++) {
		graph->insertVertex(graph, i);
	}

	Vertex* vert1 = graph->get_vertex_by_value(graph, 1);
	Vertex* vert2 = graph->get_vertex_by_value(graph, 2);
	Vertex* vert3 = graph->get_vertex_by_value(graph, 3);
	Vertex* vert4 = graph->get_vertex_by_value(graph, 4);
	Vertex* vert5 = graph->get_vertex_by_value(graph, 5);
	Vertex* vert6 = graph->get_vertex_by_value(graph, 6);

	graph->insertEdge(graph, vert1, vert2);
	graph->insertEdge(graph, vert1, vert3);
	graph->insertEdge(graph, vert2, vert3);
	graph->insertEdge(graph, vert1, vert4);
	graph->insertEdge(graph, vert3, vert4);
	graph->insertEdge(graph, vert4, vert5);
	graph->insertEdge(graph, vert5, vert6);

	//graph->deleteVertex(graph, vert4);
	Vertex** arr = graph->adjacent(graph, vert2);

//	for (int i = 0;; i++) {
//		if (arr[i] == NULL) {
//			break;
//		}
//		printf("%d ", arr[i]->data);
//	}
//
	graph->print_DFS(graph, vert3);
	return 0;
}