/* Z_i_beta = gamma* [(W_beta_bu * x_mu_i) - c ] */
/* Omega is normalized after update */
/* W is not normalized after update */
/* C has not taken account */


#include <iostream>
#include <cmath>
#include <vector>

#include "GD.h"
#include "constants.h"
#include "LossFunction.h"
#include "ActFuncPrime.h"
#include "ActFunc.h"


#define W_beta_mu(beta,mu) X[(beta)*d +(mu)]
#define Omega_beta(beta) X[Nh*(d)+(beta)]
#define C_beta(beta) X[(Nh*(d+1))+(beta)]
#define dW_beta_mu(beta,mu) dX[(beta)*d +(mu)]
#define dOmega_beta(beta) dX[Nh*(d)+(beta)]
#define dC_beta(beta) dX[(Nh*(d+1))+(beta)]
#define Z_i_beta(beta,i) Z[(i)*Nh +(beta)]

using namespace std;


void GD (vector <double> &X ,double** x,int *y,double alpha,double tol){

    vector<double> Z(Nh*p,0);               //argument of activation function Z[beta,i]=W[beta].x[i]-c{beta]
    vector<double> dX (Nh*(d+2),0);         //growth at X
    double L_new,L_old;		                //Loss func val.
    int counter=0;                          //stores #of iteration
    double dW2,dOmega2,dC2,norm;            //norm2 of each part of gradient
    double W2,Omega2;                       //for normalizing
    double error=10;                        //relative error of Loss function
    //double tol_norm = tol*sqrt((d+1)*Nh);   //tolerance for the norm1 of gradient /*WE DON'T HAVE C NOW*/



    L_new=LossFunction(X, x, y);    //Loss before GD

    int check=0;
    while ( check<10 ){ //|| (norm > tol_norm)
        //cout<<"error is "<<fabs(error)<<endl;
        if(fabs(error)<tol){ check++; }
        else{ check=0; }

        dOmega2=0;
        dW2=0;
        dC2=0;
        W2=0;
        Omega2=0;

        counter++;      //number of iterations
        L_old=L_new;    //initial loss function


        //this computes Z_beta_i(beta,i)
        for (int i=0;i<p;i++) {
            for (int beta = 0; beta < Nh; beta++) {
                Z_i_beta(beta,i) = 0;
                for (int mu = 0; mu < d; mu++) { Z_i_beta(beta,i) += x[mu][i]*W_beta_mu(beta,mu); }
                Z_i_beta(beta,i) -= C_beta(beta);
            }
        }

        //updating W and Omega
        for(int beta=0;beta<Nh;beta++) {
            for (int mu = 0; mu < d; mu++) {

                //computing dL_mu_beta
                dW_beta_mu(beta,mu) = 0;
                for (int i = 0; i < p; i++) {
                    dW_beta_mu(beta,mu) -= Omega_beta(beta)*y[i]*x[mu][i]*gamma*ActPrime(gamma*Z_i_beta(beta,i))  ; //dL/dW_beta,mu
                    dW2 += dW_beta_mu(beta,mu)*dW_beta_mu(beta,mu); //dW^2
                }
                //cout<<"mu= "<<mu<<" beta= "<<beta<<" W_old= "<<W_beta_mu(beta,mu)<<"\n";
                //cout<<"mu= "<<mu<<" beta= "<<beta<<" dW= "<<dW_beta_mu(beta,mu)<<"\n";
                W_beta_mu(beta,mu) -= alpha*dW_beta_mu(beta,mu);    //updating W
                //cout<<"mu= "<<mu<<" beta= "<<beta<<" W_new= "<<W_beta_mu(beta,mu)<<"\n";
                W2 += W_beta_mu(beta,mu)*W_beta_mu(beta,mu);        //computing W^2

            }

            for (int mu = 0; mu < d; mu++) { W_beta_mu(beta,mu)/= sqrt(W2); }    //Normalizing new Ws



            dOmega_beta(beta)=0;
//            dC_beta(beta)=0;
            for (int i = 0; i < p; i++) {
                dOmega_beta(beta) += -y[i]*Act(gamma*Z_i_beta(beta,i));
                dOmega2 += dOmega_beta(beta)*dOmega_beta(beta);     //dOmega^2

/*
                dC_beta(beta) += Omega_beta(beta)*y[i]*gamma*ActPrime(gamma*Z_i_beta(beta,i));  //dC
                dC2 += dC_beta(beta)*dC_beta(beta);     //dC^2
*/

            }
            //cout<<"beta= "<<beta<<" Omega_old= "<<Omega_beta(beta)<<"\n";
            //cout<<"beta= "<<beta<<" dOmega= "<<dOmega_beta(beta)<<"\n";
            Omega_beta(beta) -= dOmega_beta(beta)*alpha;            //updating Omega
            //cout<<"beta= "<<beta<<" Omega_new= "<<Omega_beta(beta)<<"\n";


            Omega2 += Omega_beta(beta)*Omega_beta(beta);            //computing Omega^2


            //cout<<"beta= "<<beta<<" C_old= "<<C_beta(beta)<<"\n";
            //cout<<"beta= "<<beta<<" dC= "<<dC_beta(beta)<<"\n";
//            C_beta(beta) -= dC_beta(beta)*alpha;                     //updating C
            //cout<<"beta= "<<beta<<" C_new= "<<C_beta(beta)<<"\n";
        }

        for (int beta=0;beta<Nh;beta++){ Omega_beta(beta) /= sqrt(Omega2); }     //Normalizing Omegas



        //Computing new L and errors
        L_new=LossFunction(X,x,y);    //final loss function
        error= (L_new-L_old)/L_old;
        norm = sqrt (dC2 + dW2) ; //

        //printing
        if (counter%10==0){
            //cout<<counter<<"  "<<L_old<<"   "<<L_new<<"  "<<error<<"\t "<<dW2<<"\t"<<dOmega2<<"\t"<<dC2<<"\t"<<check<<endl;
            cout<<counter<<"  "<<L_new<<"  "<<error<<"\t"<<check<<endl;
        }

    }//end of while
    cout<<"GD is done with "<<counter<<" iteration and loss is "<<L_new<<"\n";

    //return W;
}