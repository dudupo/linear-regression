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


#ifndef MATRIX
#define MATRIX

template <typename T>
class Matrix {

  T _ij_accses(size_t i ,size_t j) { return this->_matrix[i][j]; };
  T _ji_accses(size_t i ,size_t j) { return this->_matrix[j][i]; };


  T  (Matrix<T>::*get)(size_t, size_t) = &_ij_accses;
  T  (Matrix<T>::*sym)(size_t, size_t) = &_ji_accses;
  size_t _rows, _cols;

public:
  std::vector<std::vector<T>> _matrix;

  Matrix() {
    spdlog::info("matrix has been created");
  }


  Matrix( Matrix<T>& _matrix ) : Matrix() {
    // (*this) = _matrix;
    this->_rows = _matrix._rows;
    this->_cols = _matrix._cols;
    this->_matrix = _matrix._matrix;
  }

  //
  Matrix<T>& operator=( Matrix<T>& _matrix ) {
    this->_rows = _matrix.rows();
    this->_cols = _matrix.cols();
    this->_matrix = _matrix._matrix;
    return *this;
  }
  Matrix<T>& operator=( Matrix<T>&& _matrix ) {
    this->_rows = _matrix.rows();
    this->_cols = _matrix.cols();
    this->_matrix = _matrix._matrix;
    return *this;
  }

  // todo : change for any input stream
  Matrix(  const std::string &file_name ) : Matrix() {

    std::ifstream read_file(file_name);
    spdlog::info("open file : {}" ,file_name);

    read_file >> this->_rows >> this->_cols;

    this->_matrix = std::vector<std::vector<T>> (this->_rows,\
       std::vector<T>(this->_cols));

    for ( size_t i = 0; i < this->_rows; i++ )
      for (size_t j = 0; j < this->_cols; j++)
        read_file >> this->_matrix[i][j];


    read_file.close();
  }

  Matrix(size_t _rows, size_t _cols, std::vector<std::vector<T>> &_matrix) : Matrix() {
    this->_matrix = _matrix;
    this->_rows = _rows;
    this->_cols = _cols;
  }

  T operator ()(size_t i, size_t j) {
    return  (this->*get)(i,j);
  }

  Matrix& transpose( ) {
    //spdlog::info("matrix has been transposed");
    std::swap(this->get, this->sym);
    std::swap(this->_rows, this->_cols);
    return *this;
  }

  size_t cols() { return this->_cols; }
  size_t rows() { return this->_rows; }


private:

};


template <typename T>
std::vector<T>& operator *(Matrix<T>& _matrix, std::vector<T>& vec);
template <typename T>
T norm(std::vector<T>& v, std::vector<T>& u );
template <typename T>
T norm(std::vector<T>& v);
template <typename T>
std::vector<T>& normailize (std::vector<T>& vec);


std::vector<double> genraterandomVec(size_t size);
std::vector<double>& orthprojection(std::vector<double>& v,
    std::vector<double>& u);

template <typename T>
std::ostream& operator<< ( std::ostream& os, Matrix<T>& _matrix );

#include "matrix.tpp"
#endif
