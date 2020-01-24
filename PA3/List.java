/*
- Name : Rajdipa Chowdhury
- CruzID : rachowdh
- Assignment :  Programming Assignment 3

*/
public class List{
  private class Node{
    Object data;
    Node next;
    Node prev;

  // Constructor
  Node(Object data_n){
    data = data_n;
    prev = null;
    next = null;
  }
  public String toString(){
    return String.valueOf(data);
  }
  public boolean equals(Object x){
    boolean eq = false;
    Node that;
    if (x instanceof Node){
      that = (Node) x;
      eq =(this.data == that.data);
      }
      return eq;
  }
}
private Node front;
private Node back;
private Node cursor;
private int index;
private int length;
// Constructor
public List(){
  length = 0;
  front=back=null;
  cursor = null;
  index = -1;
}
public int length(){
  return length;
}

public int index(){

  if (cursor == null){
    return -1;
  }
  return index;
}

public Object front(){
  if (length <=0){
    throw new RuntimeException(
       "List Error: front() called on empty List");
  }
  return front.data;
}

public Object back(){
  if (length <=0){
    throw new RuntimeException(
       "List Error: back() called on empty List");
  }
  return back.data;
}

public Object get(){
  if (length <= 0){
    throw new RuntimeException(
       "List Error: get() called on empty List");
  }
  if (index <0){
    throw new RuntimeException(
       "List Error: get() called on Undefined cursor");
  }
  return cursor.data;
}

public boolean equals(Object x){
  if(x == null){
    return false;
  }
  boolean eq = true;
  Node n = front;
  Node n_1 = ((List)x).front;
  if (length == ((List)x).length){
     while (eq && n != null){
       eq = (n.data == n_1.data);
       n = n.next;
       n_1 = n_1.next;
       }
       return eq;
     }
  else{
  return false;
    }
  }

//  Manipulation procedures

public void clear(){
  cursor = null;
  index = -1;
  back=front=null;
  length = 0;

}
void moveFront(){
  if (length() > 0){
    cursor = front;
    index = 0;
  }
}

void moveBack(){
  if(length() > 0){
    cursor = back;
    index = length - 1;
  }
}
void movePrev(){
  //cursor is defined and at front
  if (cursor != null && index == 0){
    cursor = null;
    index = -1;
  }
  if (cursor != null && index > 0 ){
    cursor = cursor.prev;
    index--;
  }
}

void moveNext(){
  if (cursor != null && index == length-1){
    cursor = null;
    index = -1;
  }
  if (cursor != null && index > -1){
    cursor = cursor.next;
    index++;
  }

}

void prepend(Object el){
  Node temp = new Node(el);
  if (length == 0){
    front = temp;
    back = temp;
    }
    else{
      front.prev = temp;
      temp.next = front;
      front = temp;
      if (index != -1){
        index++;
      }
    }
    length++;

}

void append(Object el){
  Node temp = new Node(el);
  if (length == 0){
    front = temp;
    back = temp;
  }
  else{
    back.next = temp;
    temp.prev = back;
    back = temp;
    }
    length++;
    }
  void insertBefore(Object el){

    if (length == 0 ){
      throw new RuntimeException(
         "List Error: insertBefore() called on empty List");
    }
    if (index < 0){
      throw new RuntimeException(
         "List Error: insertBefore() called on undefined cursor");
    }
    if (index == 0){
      Node temp = new Node(el);
      temp.next = cursor;
      temp.prev = null;
      cursor.prev = temp;
      front = temp;
      length++;
      index++;
    }
    else{
      Node temp = new Node(el);
      temp.next = cursor;
      temp.prev = cursor.prev;
      cursor.prev.next = temp;
      cursor.prev = temp;
      length ++;
      index++;
    }
  }

  void insertAfter(Object el){
    if (length == 0 ){
      throw new RuntimeException(
         "List Error: insertAfter() called on empty List");
    }
    if (index < 0){
      throw new RuntimeException(
         "List Error: insertAfter() called on undefined cursor");
    }

    if (index == length - 1 ){
      Node temp = new Node(el);
      temp.prev = cursor;
      temp.next = null;
      cursor.next = temp;
      back = temp;
      length++;
    }
    else{
      Node temp = new Node(el);
      temp.prev = cursor;
      temp.next = cursor.next;
      cursor.next.prev = temp;
      cursor.next = temp;

      length++;
    }
  }
  void deleteFront(){
    if (length <= 0 ){
      throw new RuntimeException(
         "List Error: deleteFront() called on empty List");
    }
    if (cursor == front){
      cursor = null;
      index = -1;
      }
      if (index > 0){
        index--;
      }
      front = front.next;
      front.prev = null;
      length--;
    }

    void deleteBack(){
      if (length <= 0 ){
        throw new RuntimeException(
           "List Error: deleteBack() called on empty List");
      }

      if (cursor == back){
        cursor = null;
        index = -1;
      }
      if (length == 1){
        front=back=null;
      }

      back = back.prev;
      back.next = null;
      length-- ;

    }
    void delete(){
      if (length == 0 ){
        throw new RuntimeException(
           "List Error: delete() called on empty List");
      }
      if (index < 0){
        throw new RuntimeException(
           "List Error: delete() called on undefined cursor");
      }
      if (length == 1){
        front=back=null;
      }
      if (cursor == front){
        front = front.next;
        front.prev = null;
      }
      else{
        cursor.prev.next = cursor.next;
      }
      if (cursor == back){
        back = back.prev;
        back.next = null;
      }
      else{
        cursor.next.prev = cursor.prev;
      }
      cursor = null;
      index = -1;
      length--;

    }

    public String toString(){
      Node tempfront = front;
      String strnew = new String();
      while (tempfront != null){
        strnew = strnew + String.valueOf(tempfront.data) + " " ;
        tempfront = tempfront.next;
      }
      return strnew;
    }
}
