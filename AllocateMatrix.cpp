//
// Created by Arash on 11/5/2017.
//

#include "AllocateMatrix.h"


//ALLOC MATRIX FUNC
double ** AllocateMatrix(const int row, int col){
    double **mat;
    mat=new double *[row];
    for (int r=0;r<row;r++){
        mat[r]=new double[col];
    }
    return mat;
}
