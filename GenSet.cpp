/* each component of x is a gaussian of (0,1) */
/* x vectors are normalized*/
/* x are a constant random (no seed!)*/


#include <random>
#include <ctime>
#include <chrono>
#include <iostream>
#include "constants.h"
#include "GenSet.h"

using namespace std;


void GenSet  (double **x, int *y, unsigned const seed){


    // for generating random numbers
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(0.0, 1.0);

    double sum2;
    for (int i=0;i<p;i++){

        sum2=0;
        for (int mu=0;mu<d;mu++){
            //x[mu][i]=(double)(rand()-(RAND_MAX+1)/2);
            x[mu][i]=distribution(generator);
            sum2= sum2+ x[mu][i]*x[mu][i];
        }
        sum2=sqrt(sum2);
        for (int mu=0;mu<d;mu++){ x[mu][i] /= sum2;
            //cout<<x[mu][i]<<endl;
            }

        if (distribution(generator)>0){ y[i]=1; }
        else{ y[i]=-1;}

    }
}