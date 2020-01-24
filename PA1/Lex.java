/*
Rajdipa Chowdhury
cruz-iD - rachowdh
PA-1
*/



import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;


class Lex{
  public static void main(String[] args) throws IOException {

  Scanner in = null;
  PrintWriter out = null;



    String[] array = null;
    int i, lines = 0;

    //Checking for two arguments
    if (args.length != 2){
      System.err.println("Please provide correct Number of Arguments");
      System.exit(1);
      }
in = new Scanner (new File(args[0]));
out = new PrintWriter (new FileWriter(args[1]));
while (in.hasNextLine()){
  lines++;
  in.nextLine();
}
 in.close();

 List lex = new List();
 array = new String[lines];

 Scanner inp = new Scanner(new File(args[0]));

 while(inp.hasNextLine()){
   for (int a = 0; a < lines; a++){
     array[a] = inp.nextLine();

   }

 }


 if (lex.length() == 0){
   lex.append(0);}

 for (int j = 1;j < array.length; j++){
   i = j -1 ;
   String temp = array[j];
lex.moveBack();
while(i >= 0 && temp.compareTo(array[lex.get()]) <= 0){
  i--;
  lex.movePrev();
  }
   if (lex.index() >= 0){
     lex.insertAfter(j);
   }
   else{
     lex.prepend(j);
   }
 }
 lex.moveFront();
 while(lex.index() >= 0) {
   out.println(array[lex.get()]);
   lex.moveNext();
 }
 inp.close();
 out.close();
}
}
