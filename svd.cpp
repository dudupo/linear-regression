#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "spdlog/spdlog.h"
#include "matrix.h"
#include "svd.h"

// std::string printvec( std::vector<double> &v );
// std::vector<std::vector<double>> FindMapping( Matrix<double>& _matrix );
// double getSingularValueByEigenVec(Matrix<double>& _matrix,
//    std::vector<double> & eigen);
// Matrix<double>& SVD ( Matrix<double>& _matrix );



std::vector<std::vector<double>> FindMapping( Matrix<double>& _matrix ){
  spdlog::info("starting SVD deco");
  spdlog::info("generate inital condition");

  std::vector<std::vector<double>> mappMatrixU;
  _matrix = _matrix.transpose();
  for ( int j = 0; j < _matrix.rows(); j++) {

    std::vector<double> initial = genraterandomVec(_matrix.cols());
    initial = normailize(initial);

    for ( auto& vec : mappMatrixU ){
      spdlog::critical(" orthprojection -> {}", printvec(vec));
      initial =  normailize(orthprojection(initial , vec));
    }

    for ( int i = 0; i < 23; i++) {
      initial = _matrix.transpose() * initial;
      initial = normailize( _matrix.transpose() * initial );
    }

    for ( auto& vec : mappMatrixU ){
      initial = normailize(orthprojection(initial , vec));
    }

    spdlog::info("eigen vec : {}", printvec(initial));
    mappMatrixU.push_back( std::vector<double>(initial));

  }

  return mappMatrixU;
}

double getSingularValueByEigenVec(Matrix<double>& _matrix,
   std::vector<double> & eigen)
{
  std::vector<double> temp (eigen);
  temp = _matrix * temp;
  temp = _matrix.transpose() * temp;
  int i = 0;
  for(; eigen[i] == 0; i++) { }
  return std::sqrt( temp[i]/ eigen[i] );
}

SVD& genereateSVD ( Matrix<double>& _matrix ){

  std::vector<std::vector<double>>\
   eigensU = FindMapping(_matrix);


  Matrix<double> U (_matrix.cols(), _matrix.cols(), eigensU );

  std::vector<double> LAMBDAS;
  for (int i = 0; i < eigensU.size(); i++) {
    LAMBDAS.push_back(\
      getSingularValueByEigenVec( _matrix, eigensU[i] ));
  }

  std::vector<std::vector<double>>\
   eigensV = FindMapping(_matrix.transpose());

  Matrix<double> V (_matrix.rows(), _matrix.rows(), eigensV );

  SVD * ret = new SVD(U, V, LAMBDAS);
  return *ret;
}



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

  Matrix<double> _matrix(argv[1]);
  SVD& svdmatrix = genereateSVD( _matrix) ;
  std::cout << svdmatrix;
  return 0;
}
