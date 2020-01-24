import java.io.*;
import java.util.Scanner;
import java.lang.System.*;

class Sparse{
public static void main (String args[]) throws IOException{
  //checking the correct no. of arguments
  if(args.length != 2){
    System.out.printf("USAGE: Sparse inputfile outputfile ");
    System.exit(1);
  }
  Scanner inp = new Scanner(new File(args[0]));
  PrintWriter out  = new PrintWriter(new File(args[0]));

    int N_mat = Integer.parseInt(inp.next()) + 1;
    int A_mat = Integer.parseInt(inp.next());
    int B_mat = Integer.parseInt(inp.next());
    double scale = 1.5;




    Matrix A = new Matrix(A_mat);
    Matrix B = new Matrix(B_mat);

    for(int i=0;i < A_mat;i++){
      int a = Integer.parseInt(inp.next());
      int b = Integer.parseInt(inp.next());
      double d = Double.parseDouble(inp.next());
      A.changeEntry(a,b,d);

    }
  for(int j=0;j < B_mat;j++){
      int e = Integer.parseInt(inp.next());
      int f = Integer.parseInt(inp.next());
      double g = Double.parseDouble(inp.next());
      B.changeEntry(e,f,g);

    }

    //Print File
    out.println("A has"+A.getNNZ()+"non-zero entries:" );
    out.println(A);

    out.println("B has"+B.getNNZ()+"non-zero entries:" );
    out.println(B);
    out.println("(1.5)*A = " );
    out.println(A.scalarMult(1.5));
    out.println("A+B = " );
    out.println(A.add(B));
    out.println("(A+A = " );
    out.println(A.add(A));
    out.println("B-A = " );
    out.println(B.sub(A));
    out.println("A-A = " );
    out.println(A.sub(A));
    out.println("Transpose(A) = " );
    out.println(A.transpose());
    out.println("A*B = " );
    out.println(A.mult(B));
    out.println("B*B = " );
    out.println(B.mult(B));

    inp.close();
    out.close();

  }


}
