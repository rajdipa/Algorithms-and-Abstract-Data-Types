/*
Rajdipa Chowdhury
cruz id : rachowdh
pa5
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Graph.h"
#include <stdbool.h>

#define MAX_LEN 250

int main(int argc, char* argv[])
{

    FILE *input;
    FILE *output;
    char line[MAX_LEN];
    int size = 0;
    List S = newList();

   if( argc != 3 )
    {
      printf("Error:%s wrong number of arguments \n", argv[0]);
      exit(1);
   }

   input = fopen(argv[1], "r");
   output = fopen(argv[2], "w");

   if(input == NULL)
    {
      printf("Cannot open file %s\n", argv[1]);
      exit(1);
   }

   if(output == NULL)
    {
       printf("Cannot open file to write output %s", argv[2]);
       exit(1);
   }

   //reads formatted input from a string, determines size of Graph
   fgets(line, MAX_LEN, input);
   sscanf(line, "%d", &size);


   int j;
   for(j = 1; j <= size; j++)
   {
       append(S, j);
   }
  // Assemble a graph object G using newGraph() and addArc().
   Graph G = newGraph(size);
   Graph Transpose;

   while( fgets(line, MAX_LEN, input) != NULL)  {
      int a = 0;
      int b = 0;
      sscanf(line, "%d %d", &a, &b);
      if(a == 0 && b == 0)
         break;
      addArc(G, a, b);
   }


   DFS(G, S);
   Transpose = transpose(G);
   DFS(Transpose, S);
   moveFront(S);


   int scc = 0;
   while(index(S) >= 0)
    {
      if(getParent(Transpose, get(S)) == NIL)
         scc++;
      moveNext(S);
   }

   List Lscc[scc];
   int i;
   for(i = 0; i < scc; i++)
   {
      Lscc[i] = newList();
   }

   moveFront(S);
   int list = scc;
   while(index(S) >= 0)
    {
      if(getParent(Transpose, get(S)) == NIL)
         list--;
      if(list == scc)
         break;
      append(Lscc[list], get(S));
      moveNext(S);
   }


   fprintf(output, "Adjacency list representation of G:\n");
   printGraph(output, G);


   fprintf(output, "\nG contains %d strongly connected components:", scc);
   int m;
   for(m = 0; m < scc; m++)
   {

      fprintf(output, "\nComponent %d: ", (m + 1));
      printList(output, Lscc[m]);
      freeList(&(Lscc[m]));
   }
   printf("Success, output file created \n");


   freeGraph(&G);
   freeGraph(&Transpose);
   freeList(&S);


   fclose(input);
   fclose(output);
   return(0);
}
