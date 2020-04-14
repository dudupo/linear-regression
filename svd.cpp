#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "spdlog/spdlog.h"
#include <vector>
#include <fstream>
#include <string>
#include <utility>
#include <ostream>
#include <cmath>
#include <random>
#include "svd.h"


void test1 (){
  spdlog::info("starting test 1");
  Matrix<double> _matrix("./tests/test1");
  std::vector<std::vector<double>> V =  {
         { 0, 0, 0 },
         { 1, 1, 1 },
         { 2, 3, 4 },
         { -1, -2, 0 }
   };

  for (auto&  v : V ){
      spdlog::info("mull by : {}", printvec(v));
      spdlog::info("resoults : {}", printvec(_matrix* v));
  }
}
void test2 (){
  spdlog::info("test 2, testing transpose");
  Matrix<double> _matrix("./tests/test0");
  std::cout << _matrix;
  _matrix.transpose();
  std::cout << _matrix;
  _matrix.transpose();
  std::cout << _matrix;
}
void test3 () {
  spdlog::info("testing 4x3 dimensions");
  Matrix<double> _matrix("./tests/test2");
  std::cout << _matrix << '\n';
  std::cout << _matrix.transpose() << '\n';
}



int main(int argc, char const *argv[]) {

//  test1();
//  test2();

  Matrix<double> _matrix("./tests/test3");
  SVD(_matrix);

  return 0;
}
