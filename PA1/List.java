/*
Rajdipa Chowdhury
cruz-iD - rachowdh
PA-1
*/
public class List{
  private class Node{
    int data;
    Node prev;
    Node next;

    //Constructor
      Node(int data_n, Node next_n , Node prev_n){
        this.data = data_n;
        this.next = next_n;
        this.prev = prev_n;
      }
    // toString(): Overrides Object's toString()method
      public String toString(){
        return String.valueOf(data);
      }
  }
private Node front;
private Node back;
private Node cursor;
private int length;
private int index;

// Creates a new empty list
List(){
  cursor = null;
  back = null;
  front = null;
  length = 0 ;
  index = -1;
}
// Access Functions
// Returns the number of elements in this List
int length(){
   return length;
}
// If cursor is defined, returns the index of the cursor element,
 // otherwise returns -1.
 int index(){
   if(cursor == null){
     return -1 ;
   }
   else{
     return index;
   }
 }

 // Returns front element. Pre: length()>0
 int front(){
   if (length() <= 0 ){
     throw new RuntimeException(
              "List Error: front() called on empty List");
   }
   return front.data;
 }
// Returns back element. Pre: length()>0
 int back(){
   if (length() <= 0 ){
     throw new RuntimeException(
              "List Error: back() called on empty List");
   }
   return back.data;

 }
 // Returns cursor element. Pre: length()>0, index()>=0
 int get(){
   if(length() <= 0){
     throw new RuntimeException(
            "List Error: get called on empty List");
   }
   if (index()<0){
      throw new RuntimeException(
         "List Error: get() called on undefined cursor");
       }
       return cursor.data;

 }

 // Returns true if and only if this List and L are the same
 // integer sequence. The states of the cursors in the two Lists
 // are not used in determining equality.
 boolean equals(List L){
   Node temp1 = front;
   Node temp2 = L.front;
   boolean istrue = true;
   if (L.length() != length ){
     return false;
   }

   else{
            while(temp1 != null && temp2 != null){
              if(temp1.data != temp2.data ) {
                return false;
                }
                else{
                  temp1 = temp1.next;
                  temp2 = temp2.next;
                }
            }
            return istrue;

          }
        }
    // Manipulation procedures
    // Resets this List to its original empty state
    void clear(){
      cursor = null;
      front = null;
      back = null;
      length = 0;
      index = -1;
    }
    // If List is non-empty, places the cursor under the front element,
 // otherwise does nothing.
 void moveFront(){
   if(length > 0){
     cursor = front;
     index = 0;
   }
 }

 // If List is non-empty, places the cursor under the back element,
 // otherwise does nothing.
 void moveBack(){
   if(length > 0){
     cursor = back;
     index = length - 1 ;
   }
 }

 // If cursor is defined and not at front, moves cursor one step toward
 // front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing
void movePrev(){
  // If cursor is defined and not at front
  if (cursor != null && index != 0){
    cursor = cursor.prev;
    index--;
  }
  //if cursor is defined and at front
  else if (cursor != null && index == 0){
    cursor = null;
    index = -1;
  }
}

// If cursor is defined and not at back, moves cursor one step toward
 // back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing

void moveNext(){
  // If cursor is defined and not at back
  if (cursor != null && index != length -1 ){
    cursor = cursor.next;
    index++;
  }
  else if(cursor != null && index == length -1 ){
    cursor = null;
    index = -1;
  }

}

// Insert new element into this List. If List is non-empty,
 // insertion takes place before front element
 void prepend(int data){
   Node temp = new Node(data, front, null);
   if (front == null){
     back = temp;
   }
   else {
     front.prev = temp;
   }
   front = temp;
   length++ ;
 }

 // Insert new element into this List. If List is non-empty,
 // insertion takes place after back element

 void append(int data){
   Node temp = new Node(data,null,back);
   if (front == null){
     front = temp;
   }
   else{
     back.next = temp;
   }
   back = temp;
   length++ ;
 }

 // Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(int data){
  Node temp = new Node(data,cursor,cursor.prev);
  if (length< 1 ){
    throw new RuntimeException(
              "list error:Cannot call inserBefore() on an empty list");
  }
  if ( cursor == null){
    throw new RuntimeException(
        "list error:Cannot call insertBefore() on an undefined cursor");
  }
  if (cursor.prev != null){
    cursor.prev.next = temp;
  }
  else{
    front = temp;
  }
  cursor.prev = temp;
  length ++;
}

// Inserts new element after cursor.
// Pre: length()>0, index()>=0

void insertAfter(int data){
  Node temp = new Node(data,cursor.next,cursor);
  if (length< 1 ){
    throw new RuntimeException(
              "list error:Cannot call inserAfter() on an empty list");
  }
  if ( cursor == null){
    throw new RuntimeException(
        "list error:Cannot call insertAfter() on an undefined cursor");
  }
  if (cursor.next != null){
    cursor.next.prev = temp;

  }
  else{
    back = temp;
  }
  cursor.next = temp;
  length++ ;
  }
  // Deletes the front element. Pre: length()>0
  void deleteFront(){
    if (length < 1 ){
      throw new RuntimeException(
                "list error:Cannot call deleteFront() on an empty list");
    }
    if(cursor == front ){
      cursor = null;
      index = -1;
    }
    front = front.next;
    front.prev = null;
    length--;
    }

    // Deletes the back element. Pre: length()>0

    void deleteBack(){
      if (length < 1 ){
        throw new RuntimeException(
                  "list error:Cannot call deleteBack() on an empty list");
      }
      if (cursor == back){
        cursor = null;
        index = -1;
      }
      back = back.prev;
      back.next = null;
      length-- ;
      }
      // Deletes cursor element, making cursor undefined.
 	    // Pre: length()>0, index()>=0

      void delete(){
        if (length < 1 ){
          throw new RuntimeException(
                    "list error:Cannot call delete() on an empty list");
        }
        if (cursor == null ){
          throw new RuntimeException(
                    "list error:Cannot call delete() on undefined");
        }
        if (cursor == front){
          deleteFront();
        }
        else if (cursor == back){
          deleteBack();
        }
        else {
          cursor.prev.next = cursor.next;
          cursor.next.prev = cursor.prev;
          cursor = null;
          index = -1;
          length--;
        }
      }


  // Overrides Object's toString method. Returns a String
 // representation of this List consisting of a space
// separated sequence of integers, with front on left

 public String toString(){
   Node tempfront = front;
   String strnew = new String();
   while(tempfront != null){
     strnew = strnew+ String.valueOf(tempfront.data) + " " ;
     tempfront = tempfront.next;
   }
 return strnew;

 }
 // Returns a new List representing the same integer sequence as this
  // List. The cursor in the new list is undefined, regardless of the
  // state of the cursor in this List. This List is unchanged.
 List copy(){
   List newlist = new List();
   Node tempfront = front;
   while(tempfront != null){
     newlist.append(tempfront.data);
     tempfront = tempfront.next;
   }
   newlist.cursor = null;
   newlist.index = -1;
   return newlist;
 }








}
