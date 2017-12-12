//
// Created by Arash on 12/10/2017.
//

#include <cmath>
#include "ActFunc.h"

double Act(double z){
    //sigmoid
    return 1/(1+exp(-z))-0.5;

    //tanh
    //return tanh(z);

    //ReLU

    if (z>0) {return z;}
    else {return 0;}

}