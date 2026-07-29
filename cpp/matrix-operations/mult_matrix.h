/*This program multiply the rows and colums of the main matrix.*/

#ifndef MULT_MATRIX_H
#define MULT_MATRIXX_H
#include "simple_matrix.h"
#include <vector>
using namespace std;
template <typename Object>
matrix<Object> multmatrix(const matrix<Object>& a, const matrix<Object>& b){

  int rows = a.numrows();
  int cols = b.numcols();
  int inner = a.numcols();
  
  matrix<Object> result (rows, cols);
    for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
	result[i][j] = 0;
	for(int k = 0; k<inner; k++){
	  result[i][j] += a[i][k] * b[k][j];
	}
      }
    }
    return result;
  };

#endif
