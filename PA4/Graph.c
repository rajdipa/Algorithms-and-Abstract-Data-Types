
/*
Rajdipa Chowdhury
rachowdh
pa4
*/
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

typedef struct GraphObj{
  List *adj;
  int *color; // 0 = white, 1  = gray, -1 = black
  int *parent;
  int *distance;

  int order; // number of vertices
  int size; // number of edges
  int srv; // vertex that was most recently used for BFS
} GraphObj;

Graph newGraph(int n){
  Graph G;

  G = malloc (sizeof(GraphObj));
  G->adj = malloc( (n + 1) * sizeof(List));
  G->color = malloc( (n + 1) * sizeof(int));
  G->parent = malloc( (n + 1) * sizeof(int));
  G->distance = malloc( (n + 1) * sizeof(int));


  //Setting values of everything
  for(int i = 1; i < n + 1; i++){
    G->adj[i] = newList();
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->distance[i] = INF;
  }

  G->order = n;
  G->size = 0;
  G->srv = NIL;

  return G;
}

void freeGraph(Graph *pG){
  for(int i = 1; i < (*pG)->order + 1; i++){
    freeList(&(*pG)->adj[i]);
  }
  free((*pG)->adj);
  free((*pG)->color);
  free((*pG)->parent);
  free((*pG)->distance);
  free(*pG);
  *pG = NULL;
}

int getOrder(Graph G){
  if(G == NULL){
    printf("Graph error: getOrder() called on Null reference");
    exit(1);
  }
  return G->order;
}

int getSize(Graph G){
  if(G == NULL){
    printf("Graph error: getSize() called on Null reference");
    exit(1);
  }
  return G->size;
}

int getSource(Graph G){
  if(G == NULL){
    printf("Graph error: getSource() called on Null reference");
    exit(1);
  }
  return G->srv;
}

int getParent(Graph G, int u){
  if(G == NULL){
    printf("Graph error: getParent() called on Null reference");
    exit(1);
  }
  return G->parent[u];
}

int getDist(Graph G, int u){
  if(G == NULL){
    printf("Graph error: getDist() called on Null reference");
    exit(1);
  }
  return G->distance[u];
}

void getPath(List L, Graph G, int u){
  if(G == NULL){
    printf("Graph error: getPath() called on Null reference");
    exit(1);
  }
  if(G->color[u] != BLACK){
    append(L, NIL);
    return;
  }
  if(G->parent[u] == NIL){
    append(L,u);
    return;
  }
  getPath(L, G, G->parent[u]);
  append(L,u);
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
  if(G == NULL){
    printf("Graph error: makeNull() called on Null reference");
    exit(1);
  }
  for(int i = 0; i < G->order; i++){
    clear(G->adj[i]);
  }
  G->size = 0;
}
void insertList(List li, int vi){
  if(length(li) == 0){
    append(li,vi);
    return;
  }

  moveFront(li);
  while( index(li) != -1){
     if(get(li) > vi) {
       insertBefore(li, vi);
       break;
     }
    moveNext(li);
  }


  if(index(li) == -1){
    append(li, vi);
  }
}

void addEdge(Graph G, int u, int v){
  if(G == NULL){
    printf("Graph error: addEdge() called on Null reference");
    exit(1);
  }

  insertList(G->adj[u], v);
  insertList(G->adj[v], u);
  G->size++;
}

void addArc(Graph G, int u, int v){
  if(G == NULL){
    printf("Graph error: addArc() called on Null reference");
    exit(1);
  }
  insertList(G->adj[u], v);
  G->size++;
}

void BFS(Graph G, int s){
  if(G == NULL){
    printf("Graph error: BFS() called on Null reference");
    exit(1);
  }

  for(int i = 1; i <= getOrder(G); i++){
    G->color[i] = WHITE;
    G->distance[i] = INF;
    G->parent[i] = NIL;
  }
  G->srv = si;
  G->color[si] = GRAY;
  G->distance[si] = 0;
  G->parent[si] = NIL;
  List k = newList();
  append(k, si);

  while(length(k) != 0){
    int x = derow(k);
    moveFront(G->adj[x]);

    for(int i = 0; i < length(G->adj[x]); i++){
        int y = get(G->adj[x]);
        if(G->color[y] == WHITE){
          G->color[y] = GRAY;
          G->distance[y] = G->distance[x] + 1;
          G->parent[y] = x;
          append(k,y);
        }
        moveNext(G->adj[x]);
    }
    G->color[x] = BLACK;
  }

  freeList(&k);
}
int derow(List l){
  moveFront(l);
  int x = get(l);
  deleteFront(l);

  return x;
}

void printGraph(FILE* out, Graph G){
  if(G == NULL){
    printf("Graph error: printGraph() called on Null reference");
    exit(1);
  }
  for(int i = 1; i <= getOrder(G) ; i++){
    fprintf(out, "%d: ", i);
    printList(out,G->adj[i]);
    fprintf(out, "\n");
  }
}
