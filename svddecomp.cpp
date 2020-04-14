#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "spdlog/spdlog.h"
#include "matrix.h"
#include "svd.h"


std::string printvec( std::vector<double> &v ){
  std::string ret ("");
  for (auto& i : v)
    ret += "\n\t\t\t\t\t\t" + std::to_string(i);
  ret += "\n";
  return ret;
}

std::vector<std::vector<double>> FindMapping( Matrix<double>& _matrix ){
  spdlog::info("starting SVD deco");
  spdlog::info("generate inital condition");

  std::vector<std::vector<double>> mappMatrixU;
  _matrix = _matrix.transpose();
  for ( int j = 0; j < 5; j++) {

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

Matrix<double>& SVD ( Matrix<double>& _matrix ){

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

  std::cout << U << '\n';
  std::cout << V.transpose() << '\n';
  return _matrix;
}
