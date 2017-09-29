#include "exam.h"
#include "matrix.h"
#include <iostream>

using namespace exam;

Matrix flip_vert(const Matrix &m){

  int rows = m.get_num_rows();
  int cols = m.get_num_columns();
  Matrix binky(rows, cols);
  for(int x = 0; x < rows; x++){
    for(int y = 0; y < cols; y++){
      int val = binky.get_coord(x , y);
      binky.set_coord(rows - x, cols - y, val);
    }
  }
  return binky;
}
