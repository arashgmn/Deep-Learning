/* generators are seed by time: rd doesn't work*/
/* W and omega both have components of gaussian (0,1) */
/* Omega is normalized*/
/* W is not normalized */

#include <random>
#include <iostream>
#include <chrono>
#include "constants.h"
#include "init.h"

#define W_beta_mu(beta,mu) X[(beta) * d + (mu)]
#define Omega_beta(beta) X[(Nh*(d))+(beta)]
#define C_beta(beta) X[(Nh*(d+1))+(beta)]

using namespace std;

void Init(std::vector<double> &X) {

    double sum2W,sum2Omega,sum2C;     //store norm2

    // for generating random numbers
    std::mt19937 generator(time(NULL)*M_PI);
    std::normal_distribution<double> distW(0,1);        //W is a guassian with sigma of 1 on each component
    std::normal_distribution<double> distOmega(0,1);    //Omega is a gaussian with sigma of 1 ib each component


    sum2Omega=0;
    for (int beta = 0; beta < Nh; ++beta) {

        //W
        sum2W=0;
        for (int mu = 0; mu < d; ++mu) {
            W_beta_mu(beta,mu) = distW(generator);  //W[beta][mu]
            sum2W += W_beta_mu(beta,mu)*W_beta_mu(beta,mu);
        }
        sum2W= sqrt(sum2W);
        for (int mu = 0; mu < d; ++mu) { W_beta_mu(beta,mu) /= sum2W; } //Normalizing W

        //Omega
        Omega_beta(beta)= distOmega(generator);
        sum2Omega += Omega_beta(beta)*Omega_beta(beta);

        //C
        C_beta(beta) = C; //c[beta]
        //sum2C += C_beta(beta)*C_beta(beta);
    }

    sum2Omega = sqrt(sum2Omega);
    for (int beta = 0; beta < Nh; ++beta ) { Omega_beta(beta) /= sum2Omega; } //Normalizing Omega


}
