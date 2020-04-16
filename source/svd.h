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
    // std::swap( this->U, this->V);
    Matrix<double> temp (this->V);
    this->V = this->U.transpose();
    this->U = temp.transpose();
    return *this;
  }
  SVD& dagger () {
    this->transpose();
    for ( size_t i = 0; i < this->diag.size(); i++ ) {
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
  for (size_t i = 0; i < v.size(); i++)
    ret += "\n\t\t\t\t\t\t" + std::to_string(v[i]);
  ret += "\n";
  return ret;
}
std::vector<double>& operator* (SVD& _svdmatrix, std::vector<double>& vec) {
  spdlog::info("mull SVD");
  vec = _svdmatrix.getV() * vec;
  //
  // size_t length = std::min(
  //    _svdmatrix.getU().cols(), _svdmatrix.getDiag().size());
  size_t length = _svdmatrix.getU().cols();
  if ( length > vec.size() )
    spdlog::critical(" length(U) > length(v) !");
  for (size_t i = 0; i < length ; i++ ) {
      vec[i] *=  _svdmatrix.getDiag()[i];
  }
  vec.resize( length );
  vec = _svdmatrix.getU() * vec;
  return vec;
}
std::ostream& operator<< ( std::ostream& os, SVD& _svdmatrix ) {
  os << _svdmatrix.getU();
  os << printvec( _svdmatrix.getDiag() );
  os << _svdmatrix.getV();
  return os;
}

#undef Diag
