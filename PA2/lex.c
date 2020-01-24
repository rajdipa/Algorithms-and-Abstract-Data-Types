// Rajdipa Chowdhury
//Cruzid- rachowdh
//PA2
//Based on FILEIO and PA1

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include<string.h>

#define MAX_LEN 160

int main(int argc, char * argv[] ){
int count = 0;
FILE *in,*out;
char line[MAX_LEN];


if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;

    }
    rewind(in);

    char l1[count - 1][MAX_LEN];
    int l2 = -1;
    while(fgets(line, MAX_LEN, in) != NULL){
      strcpy(l1[++l2],line);
    }
    List lex = newList();
    append(lex,0);
    for (int j = 1; j < count; j++){
      char *tok = l1[j];
      int i = j-1;
      moveBack(lex);
      while(i >= 0 && strcmp(tok,l1[get(lex)]) <= 0)
      {
        --i;
        movePrev(lex);
      }
      if(index(lex) >= 0){
        insertAfter(lex,j);
      }
      else{
        prepend(lex,j);
      }

    }
    moveFront(lex);
    while(index(lex) >= 0){
      fprintf(out,"%s",l1[get(lex)]);
      moveNext(lex);
    }

    fclose(in);
    fclose(out);

    freeList(&lex);

    return 0;
  }
