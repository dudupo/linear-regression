#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "spdlog/spdlog.h"
#include "matrix.h"
#include "svd.h"


// calculating E [ x  for x in  E +- Var ]
double _summing_in_var_range( std::vector<double> vec  )
{
  // double _sum = 0; double _mean = 0;
  // for (size_t i = 0; i < vec.size(); i++) { _sum += vec[i]; }
  // double E  = _sum / vec.size(); double V  = 0;
  // for (size_t i = 0; i < vec.size(); i++) { V += std::pow(vec[i] - E, 2); }
  // V /= vec.size();
  // for (size_t i = 0; i < vec.size(); i++) {
  //   if (  std::abs(vec[i] - E)/2 < std::sqrt( V ) )
  //     _mean += vec[i];
  // }
  // spdlog::info( " mean eigen values :  {}" , _mean / vec.size() );
  // return _mean / vec.size();
  double _max = vec[0];
  for (size_t i = 0; i < vec.size(); i++) {
     _max =  vec[i] > _max ? vec[i] : _max;
  }
  return _max;


}



// patch, should be removed
std::vector<std::vector<double>>&  _transpose_matrix_patch( std::vector<std::vector<double>> &_matrix ){
  std::vector<std::vector<double>> *ret = new std::vector<std::vector<double>> ( _matrix[0].size() );
  for ( size_t i = 0; i < _matrix[0].size(); i++){
    (*ret)[i] = std::vector<double> (  _matrix.size() );
  }
  for ( size_t i = 0; i < ret->size(); i++){
    for ( size_t j = 0; j < _matrix.size(); j++){
      (*ret)[i][j] = _matrix[j][i];
    }
  }
  spdlog::info("i was here");
  return *ret;
}

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
  for (size_t i = 0; i < vec.size(); i++)
    write_file << vec[i] << " ";
}

void writesvd( const std::string &file_name, SVD & svd ) {
    spdlog::info("open file : {}" ,file_name);
    std::ofstream write_file(file_name);
    write_file << svd;
}

std::vector<std::vector<double>> FindMapping( Matrix<double>& _matrix ){
  // spdlog::info("starting SVD deco");
  // spdlog::info("generate inital condition");

  std::vector<std::vector<double>> mappMatrixU;
  _matrix = _matrix.transpose();
  for ( size_t j = 0; j < _matrix.cols(); j++) {

    std::vector<double> initial = genraterandomVec(_matrix.rows());
    initial = normailize(initial);

    for ( auto& vec : mappMatrixU ){
      //spdlog::critical(" orthprojection -> {}", printvec(vec));
      initial =  normailize(orthprojection(initial , vec));
    }

    for ( size_t i = 0; i < 100; i++) {
      initial = _matrix.transpose() * initial;
      initial = normailize( _matrix.transpose() * initial );
    }

    for ( auto& vec : mappMatrixU ){
      initial = normailize(orthprojection(initial , vec));
    }

    // spdlog::info("eigen vec : {}", printvec(initial));
    mappMatrixU.push_back( std::vector<double>(initial));

  }

  _matrix.transpose();
  return mappMatrixU;
}
double getSingularValueByEigenVec(Matrix<double>& _matrix,
   std::vector<double> & eigen){
  std::vector<double> temp (eigen);
  // spdlog::info( " getSingularValueByEigenVec ");
  // ------------------------------
  temp = _matrix * temp;
  temp = _matrix.transpose() * temp;

  // -------------------------------
  std::vector<double> eigen_values (0);
  size_t i = 0; double _sum = 0; double count = 0;
  for(; i < eigen.size(); i++) {
    if ( eigen[i] != 0 && temp[i] != 0  ) {
      eigen_values.push_back( temp[i]/ eigen[i] );
      // spdlog::info( " summing eigen value :  {}" , temp[i]/ eigen[i] ); count++;
    }
  }
  _matrix.transpose();
  //spdlog::info( " summing eigen value :  {}" , _sum );
  // spdlog::info( " summing eigen value :  {}" , _sum / count);
  return count != 0 ? std::sqrt(_summing_in_var_range( eigen_values )) : 0;
}
SVD& genereateSVD ( Matrix<double>& _matrix ){

  std::vector<std::vector<double>>\
   eigensU = FindMapping(_matrix);


  Matrix<double> U (_matrix.rows(), _matrix.rows(), eigensU );

  std::vector<double> LAMBDAS;
  //eigensU = _transpose_matrix_patch(eigensU);

  for (size_t i = 0; i < eigensU.size(); i++) {
    LAMBDAS.push_back(\
      getSingularValueByEigenVec( _matrix, eigensU[i] ));
  }

  std::vector<std::vector<double>>
   eigensV = FindMapping(_matrix.transpose());
  _matrix.transpose();
  Matrix<double> V (_matrix.cols(), _matrix.cols(), eigensV );

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

std::vector<std::vector<double>> vendermondeMatrix(std::vector<double> x, size_t degree) {
  std::vector<std::vector<double>> _matrix (x.size());

  for ( size_t j = 0; j < x.size(); j++){
    _matrix[j] = std::vector<double> ( degree );
    _matrix[j][0] = 1;
  }

  for (size_t i = 1; i < degree; i++) {
    for(size_t j = 0; j < x.size(); j++){
      _matrix[j][i] = _matrix[j][i-1] * x[j];
    }
  }
  return _matrix;
}


std::vector<double>& polyRegression(std::vector<double> X, std::vector<double> Y, size_t degree)
{
  std::vector<std::vector<double>> _lvalue_matrix = vendermondeMatrix(X, degree);
  Matrix<double> _matrix (  X.size(), degree, _lvalue_matrix);
  spdlog::info(" dimensions {}x{} ", _matrix.rows(), _matrix.cols());
  std::cout << _matrix <<'\n';
  SVD& _svd = genereateSVD(  _matrix   );
  spdlog::info(" U-> dimensions {}x{} ", _svd.getU().rows(),  _svd.getU().cols());
  spdlog::info(" V^T-> dimensions {}x{} ", _svd.getU().rows(),  _svd.getU().cols());
  std::cout << _svd << '\n';
  _svd.dagger();
  std::cout << _svd << '\n';
  return _svd * Y;
}

int main(int argc, char const *argv[]) {

  if ( std::string("--reg").compare(argv[1]) == 0 ) {
    std::vector<double> x  { 0, 1 , 2 , 3 , 4 , 5 , 6 , 7, 8, 9 };
    std::vector<double> y  { 0, 1 , 4 , 9 , 16 , 25  , 36 , 49, 64, 81};
    std::vector<double> z = polyRegression( x, y, 3 );
    std::cout << printvec(z);
  }
  else {
    Matrix<double> _matrix(argv[1]);
    SVD& svdmatrix = genereateSVD( _matrix) ;
    spdlog::info(" dimensions {}x{} ", svdmatrix.getU().rows(),  svdmatrix.getU().cols());
    spdlog::info(" dimensions {}x{} ", svdmatrix.getV().rows(),  svdmatrix.getV().cols());

    if (argc > 1) {
      std::ofstream write_file(argv[2]);
      write_file << svdmatrix.getU();
      write_file.close();
      std::ofstream write_file2(argv[3]);
      write_file2 << printvec( svdmatrix.getDiag() );
      write_file2.close();
      std::ofstream write_file3(argv[4]);
      write_file3 << svdmatrix.getV();
      write_file3.close();

      // writesvd(argv[2], svdmatrix);
    }
    else {
      std::cout << svdmatrix;
    }
  }
  return 0;
}
