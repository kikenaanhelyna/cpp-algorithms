/*This program adds the rows and colums of the main matrix.*/

#ifndef ADDMATRIX_H
#define ADDMATRIX_H

#include "simple_matrix.h"
#include <vector>
using namespace std;

template <typename Object>
matrix<Object> addmatrix(const matrix<Object>& a, const matrix<Object>& b){
  int rows = a.numrows();
  int cols = b.numcols();
  matrix<Object> result(rows,cols);
  
  for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
            result[i][j] += a[i][j] + b[i][j];
        }
      }
   return result;
};



#endif
