/*Main matrix class to interact with user. 
User can choose to do multiplication, addition or substraction 
then user provide number of rows and columns for the first and second matrixes and after 
the system provide with processed matrix.
 */
/*
This program is symply for me to use and proceed, 
main code may take some constant time to call other classe and to proccede with user input. 
Subclasses as addMatrix and MinusMatrix take some O(N^2) because it have double-nested 
for loop and MultMatrix which do multiplication uses tripled-nested for loop wich take O(N^3).  
 */

#include <iostream>
#include "simple_matrix.h"
#include "mult_matrix.h"
#include "add_matrix.h"
#include "minus_matrix.h"
using namespace std;

int main (){

  int choice;
  do {
  cout << "What would you like to do today\n";
  cout << " 1) Multiply  matrix \n 2) Substrac matrix \n 3) Add matrix \n";
  cin >> choice;

  switch(choice){
  case 1: {
    int* row1 = nullptr;
    int* col1 = nullptr;
    int* row2 = nullptr;
    int*  col2 = nullptr;
  int temp1, temp2, temp3, temp4;
  cout << "Entre the shape for the first matrix to do multiplication: \n";
  cout << "rows:";
  cin >> temp1;
  cout << "columns: ";
  cin >> temp2;

  cout << "Enter the sape for the secomd matrix: \n";
  //cout << "By defualt it will have " << col1 << " rows.\n";
  // cout << "But you still can pick the number of columns: \n";
  //
  cout << "rows:";
  cin >> temp3;
  cout << "columns: ";
  cin >> temp4;
  //
  //cin >> col2;
  row1= new int(temp1);
  col1= new int(temp2);
  row2= new int(temp3);
  col2= new int(temp4);
  if (*col1 != *row2){
    
    cout<<"To do multiplication, number of columns in first matrix must be same as number of rows in second matrix \n please try again \n";
    choice = 0;
    row1=col1=row2=col2=nullptr;
    break;
  }
  //matrix<int> m1(row1, col1);
  //matrix<int> m2(col1, col2);
  choice = 1;
matrix<int> m1(*row1, *col1);                                                 
matrix<int> m2(*row2, *col2);  
  
   cout << "Enter values for the first  matrix  \n";
   cin >> m1;
   cout << "Enter the value for the second matrix \n";
   cin >> m2;
   cout << "First matrix \n" << m1;
   cout << "Second matrix \n" << m2;

    matrix<int> mult = multmatrix(m1, m2);
    cout << "Multiplied matrixes: \n" << mult;
    delete row1; delete col1; delete row2; delete col2;

    row1=col1=row2=col2=nullptr;

  
    break;}
  case 2:{
    int row1, col1, row2, col2;

  cout << "Entre the shape for the first matrix to do substraction: \n";
  cout << "rows:";
  cin >> row1;
  cout << "columns: ";
  cin >> col1;
  choice =2;
  cout << "Second matrix will automaticly be same shape \n";

  matrix<int> m1(row1, col1), m2(row1, col1);

    cout << "Enter values for the first  matrix \n";
    cin >> m1;
    cout << "Enter the value for the second matrix \n";
    cin >> m2;
    cout << "First matrix \n" << m1;
    cout << "Second matrix \n" << m2;

   matrix<int> subs = minusmatrix(m1, m2);
   cout << "Substracted matrixes: \n" << subs;

  
   break;}
  case 3:{
int row1, col1, row2, col2;


  cout << "Entre the shape for the first matrix to do addition: \n";
  cout << "rows:";
  cin >> row1;
  cout << "columns: ";
  cin >> col1;
  cout << "Second matrix will automaticly be same shape \n";
  choice = 3;
  matrix<int> m1(row1, col1), m2(row1, col1);

    cout << "Enter values for the first  matrix \n";
    cin >> m1;
    cout << "Enter the value for the second matrix \n";
    cin >> m2;
    cout << "First matrix \n" << m1;
    cout << "Second matrix \n" << m2;

    matrix<int> add= addmatrix(m1, m2);
    cout << "Added matrixes: \n" << add;


  
    break;}
  default:
    cout << "You entered invalid numbr, please try again :( \n ";
    choice = 0;
    break;
  }
  }while (choice == 0);


  
  return 0;

}
