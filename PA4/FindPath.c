/*
Rajdipa Chowdhury
rachowdh
pa4
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "List.h"


int main(int argc, char* argv[]){
  //
  if(argc != 3){
    printf("Usage: <input file> <output file>\n");
    exit(1);
  }

  FILE *in, *out;
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");

  if( in == NULL){
    printf("Unable to open input file for reading\n");
    exit(1);
  }
  if(out == NULL){
    printf("Unable to open output file for writing\n");
    exit(1);
  }

  char line[100];

  fgets(line,100,in);

  int numVertices = atoi(line);

  Graph G = newGraph(numVertices);


  while(fgets(line, 100, in) != NULL){
    char *token;
    token = strtok(line, " ");

    int a = atoi(token);

    token = strtok(NULL, " ");

    int b = atoi(token);

    if(a == 0 && b == 0)
      break;
    else addEdge(G, a, b);
  }

  printGraph(out, G);


  while(fgets(line, 100, in) != NULL){
    char *token;
    token = strtok(line, " ");

    int a = atoi(token);

    token = strtok(NULL, " ");

    int b = atoi(token);

    if(a == 0 && b == 0)
      break;

    if(a == b){
      fprintf(out, "The distance from %d to %d is 0\n", a, b);
      fprintf(out, "A shortest %d-%d path is: %d", a,b,a);
      continue;
    }

    BFS(G, a);
    List L = newList();
    getPath(L, G, b);
    fprintf(out, "\n");

    int lengths = length(L) - 1;
    if(lengths == 0){
        fprintf(out, "The distance from %d to %d is infinity\n", a, b);
        fprintf(out, "No %d-%d path exists", a,b);
    } else{
      fprintf(out, "The distance from %d to %d is %d\n", a, b, length(L)-1);
      fprintf(out, "A shortest %d-%d path is: ", a,b);
      printList(out,L);
    }

    fprintf(out, "\n");
    freeList(&L);
  }

  freeGraph(&G);
  return 0;
}
