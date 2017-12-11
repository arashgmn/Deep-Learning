//
// Created by Arash on 12/10/2017.
//

#include <cmath>
#include "ActFuncPrime.h"


double ActPrime(double z){
    //sigmoid
    return 2/(2+exp(-z)+exp(z));

    //tanh
    //return (1-tanh(z)*tanh(z));

    //reLU
/*
    if(z<=0){return 0;}
    else {return 1;}
*/
}