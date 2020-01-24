/*
Rajdipa Chowdhury
cruz id : rachowdh
pa5
*/
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"


typedef struct GraphObj{

List *adjList;
int *colors; // 0 = white, 1  = gray, -1 = black
int *parents;
int *discover;
int *finish;

int order;
int size;
int src;
} GraphObj;


Graph newGraph(int n){
Graph G;
// allocating memory for the Graph
G = malloc (sizeof(GraphObj));
G->adjList = malloc( (n + 1) * sizeof(List));
G->colors = malloc( (n + 1) * sizeof(int));
G->parents = malloc( (n + 1) * sizeof(int));
G->discover = malloc( (n + 1) * sizeof(int));
G->finish = malloc( (n + 1) * sizeof(int));

//Setting values of everything
for(int i = 1; i < n + 1; i++){
G->adjList[i] = newList();
G->colors[i] = WHITE;
G->parents[i] = NIL;
G->discover[i] = UNDEF;
G->finish[i] = UNDEF;
}

G->order = n;
G->size = 0;

return G;
}

void freeGraph(Graph *pG){
for(int i = 1; i < (*pG)->order + 1; i++){
freeList(&(*pG)->adjList[i]);
}
free((*pG)->adjList);
free((*pG)->colors);
free((*pG)->parents);
free((*pG)->discover);
free((*pG)->finish);
free(*pG);
*pG = NULL;
}

int getOrder(Graph G){
if(G == NULL){
printf("Error:G is NULL\n");
exit(1);
}
return G->order;
}

int getSize(Graph G){
if(G == NULL){
printf("Error:G is NULL\n");
exit(1);
}
return G->size;
}

int getParent(Graph G, int u){
if(G == NULL){
printf("Error:G is NULL\n");
exit(1);
}
return G->parents[u];
}

int getDiscover(Graph G, int u){
return G->discover[u];
}

int getFinish(Graph G, int u){
return G->finish[u];
}

void makeNull(Graph G){
if(G == NULL){
printf("Error:G is NULL\n");
exit(1);
}
for(int i = 0; i < G->order; i++){
clear(G->adjList[i]);
}
G->size = 0;
}

int insertList(List l, int v){
if(length(l) == 0){
append(l,v);
return 1; //apended to list
}

moveFront(l);
while( index(l) != -1){
if(get(l) == v) // element is already in ListObj
return 0; // did not append to list
if(get(l) > v) { // current element is bigger than v
  insertBefore(l, v);
  return 1; // appened to list;
}
moveNext(l);
}

//now at the end of the list, so just append v
if(index(l) == -1){
append(l, v);
return 1; //appended to list
}

return  0; // did not append to list
}

// vertex u has a connection with vertex v
void addEdge(Graph G, int u, int v){
if(G == NULL){
printf("Error:G is NULL\n");
exit(1);
}
//do insertion at the right place
insertList(G->adjList[u], v); // inserting v into row u
insertList(G->adjList[v], u); // inserting u into row v
G->size++;
}

void addArc(Graph G, int u, int v){
if(G == NULL){
printf("Error:G is NULL\n");
exit(1);
}
if(insertList(G->adjList[u], v) == 1)
G->size++;
}

void getPath(List L, Graph G, int u){
if(G == NULL){
printf("Error:G is NULL\n");
exit(1);
}
if(G->colors[u] != BLACK){
append(L, NIL);
return;
}
if(G->parents[u] == NIL){
append(L,u);
return;
}
getPath(L, G, G->parents[u]);
append(L,u);
}

void visit(Graph G, List S, int x, int *time){
G->colors[x] = GRAY;
G->discover[x] = ++*(time);
moveFront(G->adjList[x]);
for(int i = 1; i < length(G->adjList[x]) + 1; i++){
int y = get(G->adjList[x]);
if(G->colors[y] == WHITE){
 G->parents[y] = x;
 visit(G, S, y, time);
}
moveNext(G->adjList[x]);
}
G->finish[x] = ++*(time);
prepend(S, x);
G->colors[x] = BLACK;
}

void DFS(Graph G, List S){
for(int i = 1; i < getOrder(G) + 1; i++){
G->colors[i] = WHITE;
G->parents[i] = NIL;
G->discover[i] = UNDEF;
G->finish[i] = UNDEF;
}
int time = 0;
moveFront(S);
for(int i = 1; i < getOrder(G) + 1; i++){
int x = get(S);
moveNext(S);
if(G->colors[x] == WHITE){
 visit(G, S, x, &time);
}
}

for(int i = 1; i < getOrder(G) + 1; i++ ){
deleteBack(S);
}
}

Graph transpose(Graph G){
Graph transposedGraph = newGraph(getOrder(G));

for(int i = 1; i < getOrder(G) + 1; i++){
moveFront(G->adjList[i]);
while(index(G->adjList[i]) != -1){
 append(transposedGraph->adjList[get(G->adjList[i])], i);
 //addArc(transposedGraph, get(G->adjList[i]), i);
 moveNext(G->adjList[i]);
}
}

return transposedGraph;
}

Graph copyGraph(Graph G){
Graph nGraph = newGraph(getOrder(G));
for(int i = 1; i < getOrder(G) + 1; i++){
moveFront(G->adjList[i]);
while(index(G->adjList[i]) != -1){
 append(nGraph->adjList[i],get(G->adjList[i]));
 moveNext(G->adjList[i]);
}
nGraph->colors[i] = G->colors[i];
nGraph->parents[i] = G->parents[i];
nGraph->discover[i] = G->discover[i];
nGraph->finish[i] = G->finish[i];
}
return nGraph;
}

void printGraph(FILE* out, Graph G){
if(G == NULL){
printf("Error:G is NULL\n");
exit(1);
}
for(int i = 1; i < getOrder(G) + 1; i++){
fprintf(out, "%d: ", i);
printList(out,G->adjList[i]);
fprintf(out, "\n");
}
}
