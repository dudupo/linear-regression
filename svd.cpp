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

std::vector<double>& readvec( const std::string &file_name ) {
  std::ifstream read_file(file_name);
  spdlog::info("open file : {}" ,file_name);
  int size; read_file >> size;
  std::vector<double> * ret = new std::vector<double>(size);
  for (int i = 0; i < size; i++)
    read_file >> (*ret)[i];
  return *ret;
}

void writevec( const std::string &file_name, std::vector<double>& vec ) {
  std::ofstream write_file(file_name);
  spdlog::info("open file : {}" ,file_name);
  write_file << vec.size();
  for (int i = 0; i < vec.size(); i++)
    write_file << vec[i] << " ";
}


std::vector<std::vector<double>> FindMapping( Matrix<double>& _matrix ){
  spdlog::info("starting SVD deco");
  spdlog::info("generate inital condition");

  std::vector<std::vector<double>> mappMatrixU;
  _matrix = _matrix.transpose();
  for ( int j = 0; j < _matrix.rows(); j++) {

    std::vector<double> initial = genraterandomVec(_matrix.rows());
    initial = normailize(initial);

    for ( auto& vec : mappMatrixU ){
      spdlog::critical(" orthprojection -> {}", printvec(vec));
      initial =  normailize(orthprojection(initial , vec));
    }

    for ( int i = 0; i < 25; i++) {
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
   std::vector<double> & eigen){
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


  Matrix<double> U (_matrix.rows(), _matrix.rows(), eigensU );

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

std::vector<std::vector<double>> vendermondeMatrix(std::vector<double> x, int degree)
{
  std::vector<std::vector<double>> _matrix (x.size());

  for ( int j = 0; j < x.size(); j++){
    _matrix[j] = std::vector<double> ( degree );
    _matrix[j][0] = 1;
  }

  for (int i = 1; i < degree; i++) {
    for(int j = 0; j < x.size(); j++){
      _matrix[j][i] = _matrix[j][i-1] * x[j];
    }
  }
  return _matrix;
}

std::vector<double>& polyRegression(std::vector<double> X, std::vector<double> Y, int degree)
{
  std::vector<std::vector<double>> _lvalue_matrix = vendermondeMatrix(X, degree);
  Matrix<double> _matrix (  X.size(), degree, _lvalue_matrix);
  spdlog::info(" dimensions {}x{} ", _matrix.rows(), _matrix.cols());
  std::cout << _matrix <<'\n';
  SVD& _svd = genereateSVD(  _matrix   );
  spdlog::info(" dimensions {}x{} ", _svd.getU().rows(),  _svd.getU().cols());
  std::cout << _svd.getU() << '\n';
  //_svd.dagger();
  std::cout << _svd << '\n';
  return _svd * Y;
}

int main(int argc, char const *argv[]) {

  if ( std::string("--reg").compare(argv[1]) == 0 ){
    std::vector<double> x  { 1 , 2 , 3 , 4 , 5  };
    std::vector<double> y  { 1 , 4 , 9 , 16 , 25  };
    std::vector<double> z = polyRegression( x, y, 6 );
    std::cout << printvec(z);
  }
  else {
    Matrix<double> _matrix(argv[1]);
    SVD& svdmatrix = genereateSVD( _matrix) ;
    spdlog::info(" dimensions {}x{} ", svdmatrix.getU().rows(),  svdmatrix.getU().cols());
    spdlog::info(" dimensions {}x{} ", svdmatrix.getV().rows(),  svdmatrix.getV().cols());
    std::cout << svdmatrix;
  }
  return 0;
}
