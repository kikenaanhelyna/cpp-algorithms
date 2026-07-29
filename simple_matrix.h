/*This program creates the matrix based on the user input for the main matrix.*/

#ifndef SIMPLE_MATRIX_H
#define SIMPLE_MATRIX_H

#include <vector>
using namespace std;
template <typename Object> // to store any type of data
class matrix
{
 public:
  matrix(int rows, int cols ) : array(rows) //create a matrix with row and columns, vector of vectors and resize
    {
      for (auto & thisRow : array)
	thisRow.resize(cols);
    }
  matrix(vector<vector<Object>> v) :array{v} // create matrix from vector 
  {}
  matrix (vector<vector<Object>> && v) : array {std::move(v)} // create mmatrix by moving data
  {}
  const vector<Object> & operator[](int row) const
  {return array[row];} // give access to read only element in the matrix
  vector<Object> & operator[](int row) // allow modification of matrix element
    {return array[row];}

  int numrows() const // the number of rows
  {return array.size();}
  int numcols() const // return the size of first row
  {return numrows() ? array[0].size() : 0;}
private: vector<vector<Object>> array; // to store the matrix data
 
};
template <typename Object> // to print the matrix
ostream& operator <<(ostream& out, matrix<Object>& m){
    for (int i = 0; i < m.numrows(); i++){
      for (int j = 0; j < m.numcols(); j++){
        out << m[i][j]<<" ";
      }
      out << "\n";
    }
    return out;
  }
template <typename Object> // to get the values from the user
istream& operator>>(istream& in, matrix<Object>& m){
  for(int i = 0; i<m.numrows(); i++){
    for (int j = 0; j < m.numcols(); j++){
      cout << "Enter value for position " << i << ", " << j << " => ";
      in >> m[i][j];
    }
  }
  return in;
}
#endif