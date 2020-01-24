/*
Rajdipa Chowdhury
rachowdh
pa4
*/
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#define INF -1
#define NIL -2

#define WHITE 0
#define GRAY 1
#define BLACK -1

#include "List.h"

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void insertList(List li, int vi); // helper function for addEdge and addArc
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
int derow(List l);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);

#endif
