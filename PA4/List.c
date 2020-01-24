/*
Rajdipa Chowdhury
cruzid - rachowdh
pa 4
*/
#include<stdio.h>
#include<stdlib.h>
#include "List.h"

typedef struct NodeObj{
  int data;
  struct NodeObj* next;
  struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int index;
  int length;
} ListObj;

/*****CONSTRUCTORS - DESTRUCTORS*****/
// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   return(N);
}
// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}
List newList(void){
  List L;
  L = malloc(sizeof(ListObj));
  L->front = L->back = L->cursor = NULL;
  L->length = 0;
  L->index = -1;
  return(L);
}
// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.S
void freeList(List* pL){
  if(pL != NULL && *pL != NULL){
    Node cur = (*pL)->front;
    while(cur != NULL){
      deleteFront(*pL);
      cur = (*pL)->front;
    }
    free(cur);
  }
  free(*pL);
  *pL = NULL;
}

// Access functions ---
int length(List L){
  if(L == NULL){
    printf("Invalid: calling length() on NULL List Reference");
    exit(1);
  }
  return(L->length);
}

int index(List L){
  if(L == NULL){
    printf("Invalid: calling index() on NULL List Reference");
    exit(1);
  }
  return(L->index);
}

int front(List L){
  if(L == NULL){
    printf("Invalid: calling front() on NULL List Reference");
    exit(1);
  }
  return(L->front->data);
}

int back(List L){
  if(L == NULL){
    printf("Invalid: calling back() on NULL List Reference");
    exit(1);
  }
  return(L->back->data);
}

int get(List L)
{
   if(L == NULL)
    {
      printf("Invalid: calling get() on NULL List reference");
      exit(1);
   }
   if(L->index < 0)
   {
      printf("Invalid: calling get() with an undefined index on List");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("Invalid: calling get() on empty List reference");
      exit(1);
   }
   return L->cursor->data;
}

int equals(List A, List B){
  if(A == NULL || B == NULL){
    printf("Invalid: Calling equals() on NULL List Reference");
    exit(1);
  }

  if(length(A) != length(B)){
    return(0);
  }
  Node an = A->front;
  Node bn = B->front;

  while(an != NULL){
    if(an->data != bn->data){
      an = bn = NULL;
      return(0);
    }
    else {
      an = an->next;
      bn = bn->next;
    }
  }
  return(1);
}

// Manipulation procedures ----------------------------------------------------

void clear(List L){
  if(L == NULL){
    printf("Invalid: Caling clear() on NULL List Reference");
    exit(1);
  }
  Node cur = L->front;
  while(cur != NULL){
    deleteFront(L);
    cur = L->front;
  }
  freeNode(&cur);
  L->front = L->back = L->cursor = NULL;
  L->length = 0;
  L->index = -1;
}

void moveFront(List L){
  if(L == NULL){
    printf("Invalid: Calling moveFront() on NULL List reference");
    exit(1);
  }
  if(L->length != 0){
    L->cursor = L->front;
    L->index = 0;
  }
}

void moveBack(List L){
  if(L == NULL){
    printf("Invalid: Calling moveBack() on NULL List reference");
    exit(1);
  }
  if(L->length != 0){
    L->cursor = L->back;
    L->index = L->length - 1;
  }
}

void movePrev(List L){
  if(L == NULL){
    printf("Invalid: Calling movePrev() on NULL List reference");
    exit(1);
  }
  if(L->cursor != NULL && L->index != 0){
    L->cursor = L->cursor->prev;
    L->index--;
  }else if(L->cursor != NULL && L->index == 0){
    L->cursor = NULL;
    L->index = -1;
  }
}

void moveNext(List L){
  if(L == NULL){
    printf("Invalid: Calling moveNext() on NULL List reference");
    exit(1);
  }
  if(L->cursor != NULL && L->index != L->length - 1){
    L->cursor = L->cursor->next;
    L->index++;
  }else if(L->cursor != NULL && L->index == L->length - 1){
    L->index = -1;
    L->cursor = NULL ;
  }
}
void prepend(List L,int data){
  if(L == NULL){
   printf("Invalid: Calling prepend() on NULL List reference");
   exit(1);
  }
  Node temp = newNode(data);
  temp->prev = NULL;
  temp->next = L->front;
  if(L->length > 0)
    L->front->prev = temp;
  L->front = temp;
  L->length++;
  if(L->cursor != NULL)
    L->index++;
  if(L->length == 1)
    L->back = temp;
}

void append(List L, int data){
  if(L == NULL){
    printf("Invalid: Calling append() on NULL List reference");
    exit(1);
  }
  Node temp = newNode(data);

  if(L->length == 0){
    L->front = temp;
    L->back = temp;
    L->length++;
  }else{
    L->back->next = temp;
    temp->prev = L->back;
    L->back = temp;
    L->length++;
  }
}

void insertBefore(List L, int data){
  if(L == NULL ){
    printf("Invalid: Calling insertBefore() on NULL List reference");
    exit(1);
  }
  if (L->cursor == NULL){
    printf("Invalid: Calling insertBefore() on undefined cursor");
    exit(1);
  }
  if(L->index == 0)
    prepend(L,data);
  else {
    Node temp = newNode(data);
    temp->prev = L->cursor->prev;
    temp->next = L->cursor;
    L->cursor->prev->next = temp;
    L->cursor->prev = temp;
    L->index++;
    L->length++;
  }
}

void insertAfter(List L, int data){
  if(L == NULL ){
    printf("Invalid: Calling insertAfter() on NULL List reference");
    exit(1);
  }
  if (L->cursor == NULL){
    printf("Invalid: Calling insertAfter() on undefined cursor");
    exit(1);
  }
  if(L->index == L->length - 1){
    append(L,data);
  }else {
    Node temp = newNode(data);
    L->cursor->next->prev = temp;
    temp->next = L->cursor->next;
    L->cursor->next = temp;
    temp->prev = L->cursor;
    L->length++;
  }
}

void deleteFront(List L){

  if(L == NULL){
    printf("Invalid: Calling deleteFront() on NULL List reference");
    exit(1);
  }
  if(L->length == 0){
    printf("Invalid: Calling deleteFront() on empty List");
    exit(1);
  }
  Node temp = L->front;

  if(L->length > 1){
    L->front = L->front->next;
  } else{
    L->front = L->back = NULL;
  }
  freeNode(&temp);
  L->length--;
  if(L->index == 0){
    L->index = -1;
    L->cursor = NULL;
  }
  if(L->cursor != NULL)
  {
    L->index--;
  }
}

void deleteBack(List L){
  if(L == NULL){
    printf("Invalid: Calling deleteBack() on NULL List reference");
    exit(1);
  }else if(L->length == 0){
    printf("Invalid: calling deleteBack() on an empty list");
    exit(1);
  }else if(L->length == 1){
    if(L->index == 0){
      L->index = -1;
      L->cursor = NULL;
    }
    freeNode(&L->front);
    L->front = NULL;
    L->back = NULL;
    L->length = 0;
  }else{
    if(L->cursor == L->back){
      L->cursor = NULL;
      L->index = -1;
    }
    Node temp = L->back;
    L->back = L->back->prev;
    L->back->next = NULL;
    freeNode(&temp);
    L->length--;
  }
}
void delete(List L){
  if(L == NULL ){
    printf("Invalid: Calling delete() on NULL List referece");
    exit(1);
  }
  if( L->cursor == NULL){
    printf("Invalid: Calling delete() on undefined cursor");
    exit(1);
  }

  if(L->index == 0)
    deleteFront(L);
  else{
    Node oNd = L->cursor;
    oNd->prev->next = oNd->next;
    if(L->index == L->length - 1)
      L->back = oNd->prev;
    else
      oNd->next->prev = oNd->prev;
    freeNode(&oNd);
    L->cursor = NULL;
    L->length--;
    L->index = -1;
  }
}
// Other operations
void printList(FILE *out, List L){
  moveFront(L);
  while(L->cursor != NULL){
    fprintf(out, "%d ",get(L));
    moveNext(L);
  }
}

List copyList(List L){
  if(L == NULL){
    printf("Invalid: Calling copyList() on Null reference");
    exit(1);
  }
  List tL = newList();
  Node cur = L->front;
  while(cur != NULL){
    append(tL,cur->data);
    cur = cur->next;
  }
  return(tL);
}
