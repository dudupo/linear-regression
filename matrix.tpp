template <typename T>
std::ostream& operator<< ( std::ostream& os, Matrix<T>& _matrix ){
  for ( size_t  i = 0; i < _matrix.rows(); i++ ) {
    for ( size_t j =0; j < _matrix.cols(); j++ ) {
      os << _matrix(i,j) << ' ';
    }
    os << '\n';
  }
  return os;
}


template<typename T>
std::vector<T>& operator *(Matrix<T>& _matrix, std::vector<T>& vec){
  //spdlog::info("multiple vector by Matrix -non const methd-");

  if ( _matrix.cols() != vec.size() ){
    spdlog::error("dimension not equals, Matrix {} x {}, vec {}",\
    _matrix.rows(),_matrix.cols(), vec.size());
  }

  std::vector<T> ret ( _matrix.rows() );
  for ( size_t i = 0; i <_matrix.rows(); i++ ) {
    ret[i] =  _matrix(i,0) * vec[0] ;
    for ( size_t j = 1; j <_matrix.cols(); j++ ) {
      ret[i] += _matrix(i,j) * vec[j];
    }
  }
  vec = ret;
  return vec;
}


template<typename T>
T norm(std::vector<T>& v, std::vector<T>& u ){
  T _sum = v[0]*u[0];
  for (size_t i = 1; i < v.size(); i++)
    _sum += v[i]* u[i];
  return _sum;
}

template<typename T>
T norm(std::vector<T>& v){
  return norm(v , v);
}

template<typename T>
std::vector<T>& normailize (std::vector<T>& vec){
  //spdlog::info("normailizing vector");
  T _sum = std::sqrt(norm(vec));
  if ( _sum != 0 )
    for (size_t i = 0; i < vec.size(); i++)
      vec[i] /= _sum;
  else
    spdlog::critical("ZERO vector");
  return vec;
}

std::vector<double> genraterandomVec(size_t size) {
  std::vector<double> ret (size);
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> dis(-20, 20);
  for ( size_t i = 0; i < ret.size(); i++ ) {
    ret[i] = 1 ; //dis(gen);
  }
  return ret;
}


std::vector<double>& orthprojection(std::vector<double>& v,
    std::vector<double>& u){
  //spdlog::info("calculating the projection over the orthegnal space");
  if ( u.size() != v.size() ) {
    spdlog::error("lengths of vectors not match");
  }
  double projfactor = norm(u,v);
  double squarelength = norm(u);
  for (size_t i = 0; i < v.size(); i++)
    if ( squarelength != 0 )
      v[i] -= projfactor * u[i] /squarelength;
  return v;
}
