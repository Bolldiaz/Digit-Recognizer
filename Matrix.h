// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#define DEFAULT_ROW_NUM 1
#define DEFAULT_COL_NUM 1
#define EXIT_FAILURE 1

#include <iostream>
#include <cmath>

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims {
    int rows, cols;
} matrix_dims;

class Matrix {
  int _rows, _cols, _vec_size;
  float *_vec;

 public:

/**
 * Matrix regular constructor
 * @param rows new matrix rows-size
 * @param cols new matrix cols-size
 */
  Matrix (int rows, int cols);

/**
 * Matrix default-constructor
 */
  Matrix ();

/**
 * Matrix copy-constructor
 * @param oth the copied matrix
 */
  Matrix (const Matrix &oth);

/**
 * Matrix destructor
 */
  ~Matrix ()
  {
    delete[] _vec;
  }

/**
 * the rows field getter
 * @return Matrix rows number
 */
  int get_rows () const
  {
    return _rows;
  }
/**
 * the cols field getter
 * @return Matrix cols number
 */
  int get_cols () const
  {
    return _cols;
  }

// Methods & Functions:
/**
 * transpose the matrix
 * @return reference of the matrix after transposed
 */
  Matrix &transpose ();

/**
 * vectorize the matrix
 * @return reference of the matrix after vectorized
 */
  Matrix &vectorize ();

/**
 * print matrix elements
 */
  void plain_print () const;

/**
 * dot product of this matrix and another
 * @param rhs another matrix
 * @return new matrix = the dot product
 */
  Matrix dot (const Matrix &rhs) const;

/**
 * calculate the frobenius norm of the matrix
 * @return the calculation float value
 */
  float norm () const;

/**
 * similarly the '>>' operator, read data from binary file, and fill in the
 * matrix.
 * @param is stream of the binary file
 * @param m matrix to fill
 * @return reference to the given stream
 */
  friend std::istream& read_binary_file (std::istream &is, Matrix &m);

//operators:
/**
 * the '+' operator
 * @param rhs another matrix
 * @return new matrix = this + rhs
 */
  Matrix operator+ (const Matrix &rhs) const;

/**
 * the '=' operator, update this matrix to be a copy of rhs
 * @param rhs another matrix
 * @return reference of the updated matrix
 */
  Matrix &operator= (const Matrix &rhs);

/**
 * this '*' operator perform the product of this matrix and another
 * @param rhs another matrix
 * @return new matrix = this * rhs
 */
  Matrix operator* (const Matrix &rhs) const;

/**
 * this '*' operator perform the product from *right* of this, by a float
 * number
 * @param scalar float to multiply
 * @return new matrix = this * scalar
 */
  Matrix operator* (const float &scalar) const;

/**
 * this '*' operator perform the product from *left* of a given matrix, by
 * float number
 * @param scalar float to multiply
 * @param m a given matrix
 * @return new matrix = scalar * m
 */
  friend Matrix operator* (const float &scalar, const Matrix &m);

/**
 * this '+=' operator add another matrix to this matrix by: this = this + rhs
 * @param rhs another matrix
 * @return reference to this updated matrix, after the += calculation
 */
  Matrix &operator+= (const Matrix &rhs);

/**
 * this matrix(i,j) operator
 * @param i index symbolize the row number
 * @param j index symbolize the col number
 * @return a reference to the (i,j) cell in this matrix
 */
  float &operator() (const int &i, const int &j);

/**
 * this matrix(i,j) operator
 * @param i index symbolize the row number
 * @param j index symbolize the col number
 * @return a value of the (i,j) cell in this matrix
 */
  float operator() (const int &i, const int &j) const;

/**
 * this matrix[i] operator
 * @param i index symbolize the i cell in the matrix
 * @return a reference to the [i] cell in this matrix
 */
  float &operator[] (const int &i);

/**
 * this matrix[i] operator
 * @param i index symbolize the i cell in the matrix
 * @return a value of the [i] cell in this matrix
 */
  float operator[] (const int &i) const;

/**
 * create a stream of the image represented by a given matrix
 * @param os output stream
 * @param m given Matrix
 * @return a reference to the given stream after filled with matrix details
 */
  friend std::ostream &operator<< (std::ostream &os, const Matrix &m);
};

#endif //MATRIX_H
