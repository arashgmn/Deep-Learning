//
// Created by Arash on 11/13/2017.
//


#include<ctime>
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

#include "constants.h"
#include "GenSet.h"
#include "AllocateMatrix.h"
#include "init.h"
#include "DeleteMatrix.h"
#include "Accuracy.h"
#include "GD.h"
#include "WriteFunction.h"
#include "ScalarProduct.h"

const int p=1000;
const int d=100;
const int Nh=20;
const double C=0;
const double tol=0.005;
const double alpha=.01;
const double gamma=5*sqrt(d/2);
/*const unsigned seed=std::chrono::system_clock::now().time_since_epoch().count();;
std::default_random_engine generator(seed);
*/

using namespace std;

int main(){

    //unsigned seed =1;//time(NULL);//std::chrono::system_clock::now().time_since_epoch().count();
    //std::default_random_engine generator;
    //std::default_random_engine generator(time(NULL));

    clock_t start,finish;
    start=  clock();

    int K=10;
    vector <double> X(Nh*(d+2),0);
    vector <double> BIGX(Nh*(d+2)*K,0);
    double **x, **spmat;
    auto *y=new int[p];


    //Generate data set
    x=AllocateMatrix(d,p);
    GenSet(x,y);

    fstream trained;
    trained.open ("Trained Systems.txt",std::ios::app);
    trained.setf(std::ios::showpos);
    trained.setf(std::ios::scientific);
    trained.precision(6);

    for(int k=0;k<K;k++){

        //unsigned seed = time(NULL)*generator;//std::chrono::system_clock::now().time_since_epoch().count()
        //Initialize
        Init(X);
        //Training
        GD (X ,x,y, alpha, tol);
        cout<<"Accuracy is: "<<Accuracy(X,x,y)<<"%\n";
        WriteFunction(X,trained,BIGX,k);
    }

    spmat=ScalarProduct(BIGX,K);

/*
    //Variables that store optimum for all runs
    double **W_GD,**W_SG,**C_SG,**C_GD;
    W_GD=AllocateMatrix(d*Nh,N);
    C_GD=AllocateMatrix(Nh,N);
    W_SG=AllocateMatrix(d*Nh,N);
    C_SG=AllocateMatrix(Nh,N);

    //initialization of w and c : index 0 is for GD and 1 is for SG
    double **W0,**W1;
    W0=AllocateMatrix(d,Nh);
    auto *c0=new double [Nh];
    W1=AllocateMatrix(d,Nh);
    auto *c1=new double [Nh];





    for (int dummy=0;dummy<N;dummy++){

        //initialization


        CopyMatrix(W1,W0,d,Nh);
        CopyVector(c1,c0,Nh);

        clock_t start_G=  clock();

        GD(W0,c0,x,y,alpha,tol);

        SG(W1,c1,x,y,alpha,tol);
        clock_t finish_G=  clock();
        Interpolate (W1,W0,c1, c0,x,y, "interpolation");
        LinearComb (W1,W0,c1, c0,x,y, "Linear Combination", 2, 3);
        clock_t finish_I=  clock();

        //CopySuperMatrix(W_GD,W0,d,Nh,dummy,"GD");
        //CopySuperMatrix(W_SG,W1,d,Nh,dummy,"SG");
        //CopySuperVector(C_GD,c0,Nh,dummy);
        //CopySuperVector(C_SG,c1,Nh,dummy);


        //This part is to know how much time does it take for both gradients and the interpolation
        cout<<"runtime of grad [s] "<<(float)(finish_G-start_G)/CLOCKS_PER_SEC<<endl;
        cout<<"runtime of inter [s] "<<(float)(finish_I-finish_G)/CLOCKS_PER_SEC<<endl;

    }
*/
    trained.close();
    DeleteMatrix(x,d);
    //cout<<"after delete";
    finish=  clock();
    cout<<"runtime [s] "<<(float)(finish-start)/CLOCKS_PER_SEC<<endl;
    //system("pause");

}