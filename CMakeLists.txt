cmake_minimum_required(VERSION 3.9)
project(DeepLearning)

set(CMAKE_CXX_STANDARD 11)

add_executable(DeepLearning main.cpp GD.cpp GD.h init.cpp init.h init.h AllocateMatrix.cpp AllocateMatrix.h constants.cpp constants.h GenSet.cpp GenSet.h LossFunction.cpp LossFunction.h Accuracy.cpp Accuracy.h DeleteMatrix.cpp DeleteMatrix.h ActFunc.cpp ActFunc.h ActFuncPrime.cpp ActFuncPrime.h WriteFunction.cpp WriteFunction.h ScalarProduct.cpp ScalarProduct.h)