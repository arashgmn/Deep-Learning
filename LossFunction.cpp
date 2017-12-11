/* z = [(W_beta_bu * x_mu_i) - c ] */



#include <iostream>
#include <vector>
#include "constants.h"
#include "LossFunction.h"
#include "ActFunc.h"


#define W_beta_mu(beta,mu) X[(beta)*d +(mu)]
#define Omega_beta(beta) X[Nh*(d)+(beta)]
#define C_beta(beta) X[(Nh*(d+1))+ (beta)]


double LossFunction (std::vector<double> &X, double **x,  int *y){

    double L=0; //loss value
    double z=0; //z[beta][i]

    for (int i=0;i<p;i++){
        for(int beta=0;beta<Nh;beta++){
            z=0;
            for (int mu=0;mu<d;mu++){ z+= W_beta_mu(beta,mu)*x[mu][i]; }
            z -= C_beta(beta);

            L = L -Omega_beta(beta)*y[i]*Act(gamma*z);
        }
    }

    //cout<<"L is"<<L<<endl;
    return L;
}