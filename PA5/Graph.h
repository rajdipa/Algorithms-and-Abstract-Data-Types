/*
Rajdipa Chowdhury
cruz id : rachowdh
pa5
*/

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#define INF -1
#define NIL -2

#define UNDEF -1

#define WHITE 0
#define GRAY 1
#define BLACK -1
#include "List.h"

typedef struct GraphObj* Graph;


Graph newGraph(int n);
void freeGraph(Graph* pG);
/* Access functions */
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
void getPath(List L, Graph G, int u);
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
/* Manipulation procedures */
void makeNull(Graph G);
int insertList(List l, int v); // helper function for addEdge and addArc
void addEdge(Graph G, int u, int v); // unidirected edge
void addArc(Graph G, int u, int v); // directed edge
void visit(Graph G, List S, int x, int* time);
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif
