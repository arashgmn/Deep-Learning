

#define W_beta_mu(beta,mu) X[(beta) * d + (mu)]
#define Omega_beta(beta) X[(Nh*(d))+(beta)]
#define C_beta(beta) X[(Nh*(d+1))+(beta)]

#include <iostream>
#include <vector>

#include "constants.h"
#include "ActFunc.h"

using namespace std;

double Accuracy(std::vector<double> &X, double **x, int *y){
    double y_tilda,z;
    double Acc=0;
    for (int i=0;i<p;i++){
        y_tilda=0;
        for (int beta=0;beta<Nh;beta++){

            z=0;
            for (int mu=0; mu<d;mu++){ z += W_beta_mu(beta,mu)*x[mu][i]; }
            z -= C_beta(beta);

            y_tilda += Omega_beta(beta)*Act(gamma*z);

            //cout<<"z after training\t"<<z<<endl;
        }

        //cout<<y_tilda<<"\t"<<y[i]<<endl;
        if (y_tilda*y[i]>=0){

            Acc++;
        }
    }
    return Acc/p*100;
}

