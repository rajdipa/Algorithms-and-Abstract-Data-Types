//Rajdipa Chowdhury
//Cruzid: rachowdh
//PA2
//Based on Queue.c and PA1


#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs
// private NodeObj type
typedef struct NodeObj{
  int data;
  struct NodeObj* next;
  struct NodeObj* prev;
}NodeObj;
// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;

} ListObj;
// Constructors-Destructors

// newNode()
// Returns reference to new Node object. Initializes next, prev and data fields.
// Private

Node newNode(int data_n, Node prev_n, Node next_n ){
   Node N = malloc(sizeof(NodeObj));
   N->data = data_n;
   N->next = next_n;
   N->prev = prev_n;

   return(N);
}
// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private

void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}
// newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) {
      Node n = (*pL)->front;
      while(n != NULL){
        Node p = n;
        n = n->next;
        free(p);
      }
      free(*pL);
      *pL = NULL;
   }
}

//Access Functions

int length(List L){
  if ( L==NULL ){
    printf("List Error: calling length() on NULL List reference\n");
    exit(1);
    }
    return (L->length);
}
// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int index(List L){
  if ( L==NULL ){
    printf("List Error: calling index() on NULL List reference\n");
    exit(1);
    }
    if(L->cursor == NULL){
      L->index = -1;
    }
    return (L->index);
}
// Returns front element. Pre: length()>0
int front(List L){
  if ( L==NULL ){
    printf("List Error: calling front() on NULL List reference\n");
    exit(1);
    }
    if(L->length <= 0){
      printf("List Error: calling front() on an empty List\n");
      exit(1);
    }
    return (L->front->data);
  }
  // Returns back element. Pre: length()>0
   int back(List L){
     if ( L==NULL ){
       printf("List Error: calling back() on NULL List reference\n");
       exit(1);
       }
       if(L->length <= 0){
         printf("List Error: calling back() on an empty List\n");
         exit(1);
       }
    return (L->back->data);
    }

  // Returns cursor element. Pre: length()>0, index()>=0
    int get(List L){
      if ( L==NULL ){
        printf("List Error: calling get() on NULL List reference\n");
        exit(1);
        }
        if(L->length <= 0){
          printf("List Error: calling get() on an empty List\n");
          exit(1);
        }
        if (L->index < 0){
          printf("List Error: calling get() on a List with undefined cursor\n");
          exit(1);
        }
        return L->cursor->data;
      }
    int equals(List A, List B){

      if(A == NULL || B == NULL){
        printf("List Error: calling equals() on NULL List reference\n");
        exit(1);
      }
      if(A->length != B->length){
        return 0;
      }

      Node N = A->front;
      Node M = B->front;
      int ct = 1;
      while (ct && M != NULL){
	ct = (N->data == M->data);
	N = N->next;
	M = M->next;
	}
	return ct;

      }


        // Manipulation procedures

        // Resets this List to its original empty state
        void clear(List L){
          if ( L==NULL ){
            printf("List Error: calling clear() on NULL List reference\n");
            exit(1);
            }

            Node eph = L->front;
            while (eph != NULL){
              Node cur = eph;
              eph = eph->next;
              free(cur);
            }
            L->front = NULL;
            L->back = NULL;
            L->cursor = NULL;

            L->length = 0;
            L->index = -1;
            }
            // If List is non-empty, places the cursor under the front element,
            // otherwise does nothing.

            void moveFront(List L){
              if ( L == NULL ){
                printf("List Error: calling moveFront() on NULL List reference\n");
                exit(1);
                }
                if(L->length > 0){
                  L->cursor = L->front;
                  L->index = 0;
                }
              }
              // If List is non-empty, places the cursor under the back element,
              // otherwise does nothing.

              void moveBack(List L){
                if ( L==NULL ){
                  printf("List Error: calling moveBack() on NULL List reference\n");
                  exit(1);
                   }
                  if(L->length > 0){
                    L->cursor = L->back;
                    L->index = L->length - 1;
                  }
                }

                // If cursor is defined and not at front, moves cursor one step toward
                 // front of this List, if cursor is defined and at front, cursor becomes
                // undefined, if cursor is undefined does nothing.

                void movePrev(List L){
                  if ( L==NULL ){
                    printf("List Error: calling movePrev() on NULL List reference\n");
                    exit(1);
                    }
                    if (L->index > 0 &&  L->cursor != NULL ){
                      L ->cursor = L->cursor->prev;
                      --L->index;
                    }

                  else if(L->index == 0 && L->cursor != NULL){
                    L->cursor = NULL;
                    L->index = -1;
                  }
                }
                // If cursor is defined and not at back, moves cursor one step toward
                 // back of this List, if cursor is defined and at back, cursor becomes
                // undefined, if cursor is undefined does nothing.
                void moveNext(List L){
                  if ( L==NULL ){
                    printf("List Error: calling moveNext() on NULL List reference\n");
                    exit(1);
                    }
                    if (L->index != L->length - 1   &&  L->cursor != NULL ){
                      L ->cursor = L->cursor->next;
                      ++L->index;
                    }
                    else if (L->index == L->length - 1 && L->cursor != NULL){
                      L->cursor = NULL;
                      L->index = -1;

                    }
                  }

                  // Insert new element into this List. If List is non-empty,
                   // insertion takes place before front element.
                  void prepend(List L, int data){
                    if ( L==NULL ){
                      printf("List Error: calling prepend() on NULL List reference\n");
                      exit(1);
                      }
                      Node nw = newNode(data,NULL,L->front);
                      if(L->front == NULL){
                        L->back = nw;
                      }
                      else{
                        L->front->prev = nw;
                      }
                      L->front = nw;
                      ++L->length;
                     }

                     // Insert new element into this List. If List is non-empty,
                      // insertion takes place after back element.
                     void append(List L, int data){
                       if ( L==NULL ){
                         printf("List Error: calling append() on NULL List reference\n");
                         exit(1);
                         }
                         Node np = newNode(data,L->back,NULL);
                         if(L->front == NULL){
                           L->front = np;
                         }
                         else{
                           L->back->next = np;
                           }
                           L->back = np;
                           ++L->length;
                        }
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
  if ( L==NULL ){
    printf("List Error: calling insertBefore() on NULL List reference\n");
    exit(1);
    }
    if (L->length <= 0){
      printf("List Error: calling insertBefore() on an empty List");
      exit(1);

    }
    if (L->index < 0){
      printf("List Error: calling insertBefore() on undefined cursor");
      exit(1);
    }
    Node n = newNode(data,L->cursor->prev,L->cursor) ;
    if (L->cursor->prev != NULL){
      L->cursor->prev->next = n;
    }
    else{
      L->front = n;
      }
      L->cursor->prev = n;
      ++L->length;
    }
    // Inserts new element after cursor.
     // Pre: length()>0, index()>=0
    void insertAfter(List L, int data){
      if ( L==NULL ){
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(1);
        }
        if (L->length <= 0){
          printf("List Error: calling insertAfter() on an empty List");
          exit(1);

        }
        if (L->index < 0){
          printf("List Error: calling insertAfter() on undefined cursor");
          exit(1);
        }
        Node p = newNode(data,L->cursor,L->cursor->next);
        if(L->cursor->next != NULL){
          L->cursor->next->prev = p;
        }
        else{
          L->back = p;
          }
        L->cursor->next = p;
        ++L->length;

    }

    // Deletes the front element. Pre: length()>0
     void deleteFront(List L){
       if ( L==NULL ){
         printf("List Error: calling deleteFront() on NULL List reference\n");
         exit(1);
         }
         if (L->length <= 0){
           printf("List Error: calling deleteFront() on an empty List");
           exit(1);

         }
         if(L->cursor == L->front){
           L->cursor = NULL;
           L->index = -1;
         }
         Node nfront = L->front;
         L->front = L->front->next;
         L->front->prev = NULL;
         --L->length;
         freeNode(&nfront);
         }

         // Deletes the back element. Pre: length()>0
          void deleteBack(List L){
            if ( L==NULL ){
              printf("List Error: calling deleteBack() on NULL List reference\n");
              exit(1);
              }
              if (L->length <= 0){
                printf("List Error: calling deleteBack() on an empty List");
                exit(1);
                }
                if(L->cursor == L->back){
                  L->cursor = NULL;
                  --L->index;
                }
                Node nback = L->back;
                L->back = L->back->prev;
                L->back->next = NULL;
                --L->length;
                freeNode(&nback);
            }

            // Deletes cursor element, making cursor undefined.
            // Pre: length()>0, index()>=0
             void delete(List L){
               if ( L==NULL ){
                 printf("List Error: calling delete() on NULL List reference\n");
                 exit(1);
                 }
                 if (L->length <= 0){
                   printf("List Error: calling delete() on an empty List");
                   exit(1);

                 }
                 if (L->index < 0){
                   printf("List Error: calling delete() on undefined cursor");
                   exit(1);
                 }
                 if(L->cursor == L->front){
                   deleteFront(L);
                  }
                  if(L->cursor == L->back){
                    deleteBack(L);
                    }
                  else{
		    Node t = L->cursor;
                    L->cursor->prev->next = L->cursor->next;
                    L->cursor->next->prev = L->cursor->prev;
                    freeNode(&t);
                    L->cursor = NULL;
                    L->index = -1;
                    --L->length;


                  }
                }

                  // Other operations
                  //  prints the L to the file pointed to by out, formatted as a space-separated string
                  void printList(FILE* out, List L){

                    Node tem = L->front;
                    while(tem != NULL){
                      printf("%d", tem->data);
		      printf(" ");
                      tem = tem->next;
                    }

                  }

          // Returns a new List representing the same integer sequence as this
          // List. The cursor in the new list is undefined, regardless of the
           // state of the cursor in this List. This List is unchanged
                  List copyList(List L){
                    List cop = newList();
                    Node tem = L->front;
                    while(tem != NULL){
                      append(cop,tem->data);
                      tem = tem->next;
                    }
                    return cop;

                  }
