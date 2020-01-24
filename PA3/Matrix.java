/*
- Name : Rajdipa Chowdhury
- CruzID : rachowdh
- Assignment :  Programming Assignment 3

*/
public class Matrix{
  private class Entry{
    int column;
    double data;
// Constructor
Entry(int col , double val ){
  column = col;
  data = val;

}
// toString(): Overrides Object's toString()method
public String toString(){
  return "("+ column + ", "+ data +")";
}
// equals(): overrides Object's equals() method
public boolean equals(Object x){
  boolean eq = false;
  Entry that;
  if(x instanceof Entry ){
    that = (Entry) x;
    eq = (column == that.column && data == that.data );
    }
    return eq;
    }
  }


  List[] matrix;


  // Constructor
   // Makes a new n x n zero Matrix. pre: n>=1
 Matrix(int n){
   if (n < 1){
     throw new RuntimeException("Matrix Error: Matrix() called on negative size");
   }
   matrix = new List[n+1];

   for (int i =1 ; i <= n ;i++ ){
     matrix[i] = new List();
      }
    }
    // Access functions
 // Returns n, the number of rows and columns of this Matrix
   int getSize(){
     return matrix.length - 1;
   }
// Returns the number of non-zero entries in this Matrix
int getNNZ(){
  int nnz = 0;
  for (int i = 1; i <= getSize(); i++ ){
    nnz += matrix[i].length();
    }
    return nnz;
}
// overrides Object's equals() method
public boolean equals(Object x){
  Matrix mat;
  if(x instanceof Matrix){
    mat = (Matrix) x;
    if(getSize() != mat.getSize()){
      return false;
    }
    for (int i = 1; i <= getSize(); i++ ){
      if (!(matrix[i].equals(mat.matrix[i]))){
        return false;
          }
        }
      }
  return true;
}

// Manipulation procedures
// sets this Matrix to the zero state
void makeZero(){
for (int i = 1; i <= getSize(); i ++){
  matrix[i] = new List();
  }
}

// returns a new Matrix having the same entries as this Matrix
Matrix copy(){
  Matrix m = new Matrix(getSize());
  for(int i = 1; i <= getSize(); i++){
    matrix[i].moveFront();
    while (matrix[i].index() >= 0){
      Entry temp = (Entry) matrix[i].get();
      m.changeEntry(i,temp.column,temp.data);
      matrix[i].moveNext();
    }
  }
  return m;
  }

  // changes ith row, jth column of this Matrix to x
   // pre: 1<=i<=getSize(), 1<=j<=getSize()
   void changeEntry(int i, int j, double x){
     if (i <1 || i > getSize()){
       throw new RuntimeException("Matrix Error: i must be greater that equal to 1 and less than equal to the size");
     }
     if (j < 1 || j > getSize()){
       throw new RuntimeException("Matrix Error: j must be greater that equal to 1 and less than equal to the size");
     }
     boolean eq = false;
     matrix[i].moveFront();
     while (matrix[i].index() >= 0){
       Entry row = (Entry) matrix[i].get();
       if(row.column == j ){
         eq = false;
       }
       else{
         eq = false;
       }
       if (eq){
         if(x == 0.0){
           matrix[i].delete();
           return;
         }
         else{
           row.data = x;
           return;
         }
       }
       matrix[i].moveNext();
     }
      if (!eq && x != 0.0){
        matrix[i].moveFront();
        if (matrix[i].index() == -1){
          matrix[i].append(new Entry(j,x));
          return;
        }
        else{
          while(matrix[i].index() >= 0 && ((Entry) matrix[i].get()).column < j ){
            matrix[i].moveNext();
          }
          if (matrix[i].index() >= 0){
            matrix[i].insertBefore(new Entry(j,x));
            return;
          }
          else{
            matrix[i].append(new Entry(j,x));
            return;
          }
        }
      }
    }

   // returns a new Matrix that is the scalar product of this Matrix with x
   Matrix scalarMult(double x){
     Matrix m = copy();

     for (int i = 1; i <=getSize(); i++){
       m.matrix[i].moveFront();
       while(m.matrix[i].index() >=0){
         Entry t = (Entry) m.matrix[i].get();
         m.changeEntry(i,t.column,(x * t.data));
         m.matrix[i].moveNext();
       }
     }
      return m;
    }

    // returns a new Matrix that is the transpose of this Matrix
    Matrix transpose(){
      Matrix mat = new Matrix(getSize());
      for(int i =1;i<= getSize();i++){
        matrix[i].moveFront();
        while(matrix[i].index() >= 0){
          mat.changeEntry(((Entry)matrix[i].get()).column,i,((Entry)matrix[i].get()).data);
          matrix[i].moveNext();
        }
      }
      return mat;
    }

    // returns a new Matrix that is the sum of this Matrix with M
 // pre: getSize()==M.getSize()
 private List addSub(List P, List Q, boolean go) {
    List list = new List();
    P.moveFront();
    Q.moveFront();
    double ret;
    if(go)
    {
      ret = 1.0;
    }
    else
    {
      ret = -1.0;
    }
    while(P.index() >= 0 || Q.index() >= 0) {
       if(P.index() >= 0 && Q.index() >= 0) {
          Entry a = (Entry) P.get();
          Entry b = (Entry) Q.get();
          if(a.column > b.column) {
            list.append(new Entry(b.column, (ret) * b.data));
             Q.moveNext();
          } else if(a.column < b.column) {
            list.append(new Entry(a.column, a.data));
             P.moveNext();
          } else if(a.column == b.column) {
             if((go && a.data + b.data != 0) || (!go && a.data - b.data != 0))
               if(go)
               {
                 ret = a.data + b.data;
               }
               else
               {
                 ret = a.data - b.data;
               }
             list.append(new Entry(a.column, (ret)));
             P.moveNext();
             Q.moveNext();
          }
       } else if(P.index() >= 0) {
          Entry a = (Entry) P.get();
          list.append(new Entry(a.column, a.data));
          P.moveNext();
       } else {
          Entry b = (Entry) Q.get();
          list.append(new Entry(b.column, (ret) * b.data));
          Q.moveNext();
       }
    }
    return list;
 }

 Matrix add(Matrix M) {
    if(getSize() != M.getSize())
       throw new RuntimeException("Matrix: add() called on Matrix");
    if(M == this)
       return copy().scalarMult(2);
    Matrix mat = new Matrix(getSize());
    for(int i = 1; i <= getSize(); i++) {
        mat.matrix[i] = addSub(matrix[i], M.matrix[i], true);
    }
    return mat;
 }


 Matrix sub(Matrix M) {
    if(getSize() != M.getSize())
       throw new RuntimeException("Matrix: sub() called on Matrix");
    if(M == this) {
       return new Matrix(getSize());
    }
    Matrix mat = new Matrix(getSize());
    for(int i = 1; i <= getSize(); i++) {
       mat.matrix[i] = addSub(matrix[i], M.matrix[i], false);
    }
    return mat;
 }
// Vector dot product
private static double dot(List P, List Q){
  double vp = 0.0;
  Entry p, q;
  if (P.length() != 0 && Q.length() != 0){
    P.moveFront();
    Q.moveFront();
     while (P.index() >= 0 || Q.index() >= 0){
       p = (Entry) P.get();
       q = (Entry) Q.get();
       if (p.column == q.column){
         vp = vp + (p.data * q.data);
         P.moveNext();
         Q.moveNext();
       }
       else if (p.column > q.column){
         Q.moveNext();
       }
       else {
         P.moveNext();
       }
     }
  }
  return vp;
}
// returns a new Matrix that is the product of this Matrix with M
 // pre: getSize()==M.getSize()
 Matrix mult(Matrix M) {
    if(getSize() != M.getSize())
       throw new RuntimeException("Matrix: mult() called on Matrix");
    Matrix mat = new Matrix(getSize());
    Matrix A = M.transpose();
    for(int i = 1; i <= getSize(); i++) {
       if(matrix[i].length() == 0) continue;
       for(int j = 1; j <= getSize(); j++) {
          if(A.matrix[j].length() == 0) continue;
          mat.changeEntry(i, j, dot(matrix[i], A.matrix[j]));
       }
    }
    return mat;
 }
// overrides Object's toString() method
public String toString(){
  String pr = "";
  for (int i = 1; i<= getSize();i++){
    if (matrix[i].length() > 0){
      pr = pr + (i+":"+ matrix[i] + "\n");
      }
    }
    return pr;
    }


}
