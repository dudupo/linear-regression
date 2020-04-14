#include "matrix.h"


#define Diag std::vector<double>
// todo -

class SVD {

  Matrix<double> U;
  Matrix<double> V;
  Diag diag;
  //Matrix<double> &diag;

public:
  SVD( Matrix<double> U, Matrix<double> V, Diag diag) :  U(U), V(V), diag(diag)  {
    spdlog::info("creating SVD matrix");
  }
  SVD& transpose() {
    Matrix<double> * temp =  &this->U;
    Matrix<double> * temp2 = &this->V;
    this->U = *temp2;
    this->V = *temp;
    return *this;
  }
  SVD& dagger () {
    this->transpose();
    for ( int i = 0; i < this->diag.size(); i++ ) {
      if ( this->diag[i] != 0  ) {
        this->diag[i] = 1 / this->diag[i];
      }
    }
    return *this;
  }
  Matrix<double>& getU( ){
    return this->U;
  }
  Matrix<double>& getV( ){
    return this->V;
  }
  Diag& getDiag() {
    return this->diag;
  }
  friend std::ostream& operator<< ( std::ostream& os, SVD& _svdmatrix );

private:
};
std::string printvec( std::vector<double> &v ){
  std::string ret ("");
  for (int i = 0; i < v.size(); i++)
    ret += "\n\t\t\t\t\t\t" + std::to_string(v[i]);
  ret += "\n";
  return ret;
}
std::vector<double>& operator* (SVD& _svdmatrix, std::vector<double>& vec) {
  spdlog::info("mull SVD");
  std::cout << printvec( vec );
  vec = _svdmatrix.getV() * vec;
  std::cout << printvec( vec );
  for ( int i = 0; i < vec.size(); i++ ) {
    vec[i] *=  _svdmatrix.getDiag()[i];
  }
  spdlog::info("mull Diag");
  std::cout << printvec( vec );
  vec = _svdmatrix.getU() * vec;
  std::cout << printvec( vec );
  return vec;
}
std::ostream& operator<< ( std::ostream& os, SVD& _svdmatrix ) {
  os << _svdmatrix.getU();
  os << printvec( _svdmatrix.getDiag()  );
  os << _svdmatrix.getV();
  return os;
}

#undef Diag
