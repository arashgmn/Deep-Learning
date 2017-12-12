//
// Created by Arash on 12/11/2017.
//

#include "WriteFunction.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


void WriteFunction(std::vector<double> &X, fstream &trained, std::vector<double> &BIGX,int k) {
    int Size=X.size();

    for (int s=0;s<Size;s++){
        trained << X[s]<<"\t";
        BIGX[k*Size+s]= X[s];
    }
    trained<<"\n";

}
