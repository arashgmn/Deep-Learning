//
// Created by Arash on 12/12/2017.
//

#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include "ScalarProduct.h"
#include "AllocateMatrix.h"
using  namespace std;

#define Xik(i,k) BigX[(k)*Size+(i)]
#define Xjk(j,k) BigX[(k)*Size+(j)]


double** ScalarProduct (std::vector<double> &BigX,int K){
    double **spmat;
    int Size=BigX.size()/K;
    spmat=AllocateMatrix(K,K);
    double dummy;


    fstream SP;
    SP.open ("Scalar Product.txt",std::ios::app);
    SP.setf(std::ios::showpos);
    SP.setf(std::ios::scientific);
    SP.precision(6);


    for (int k=0;k<K;k++){
        dummy=0;
        for (int j=0;j<Size;j++){
            dummy+= Xjk(j,k)* Xjk(j,k);
        }
        spmat[k][k]= sqrt( dummy);
    }

    for (int i=0;i<K;i++){
        for (int j=0;j<i;j++){
            dummy=0;
            for (int k=0;k<Size;k++){
                dummy+= Xjk(k,j)*Xik(k,i);
            }
            spmat[i][j]=dummy/(spmat[i][i]*spmat[j][j]);
            spmat[j][i]=spmat[i][j];
            SP<<spmat[i][j]<<"\t";
            //cout<<dummy<<endl;
        }
        SP<<"\n";
    }


    SP.close();
    return spmat;
}