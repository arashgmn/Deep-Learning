//
// Created by Arash on 11/5/2017.
//
#include "DeleteMatrix.h"
double** DeleteMatrix(double **mat, int row){
    for (int r=0;r<row;r++){
        delete[] mat[r];
    }
    delete[] mat;
}