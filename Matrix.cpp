#include "Matrix.h"

#define PRINT_IMAGE_FACTOR_VALUE 0.1

#define FILE_NOT_OPEN_ERROR "Error: A not-opened file was given.\n"
#define INVALID_ROWS_COLS_NUM_ERROR "Error: # Cols/Rows must be >= 0.\n"
#define BYTES_NUM_NOT_SUIT_MATRIX_ERROR "Error: #bytes in file not suit the" \
                                        " number of floats in matrix.\n"
#define INVALID_MATRIX_SIZE_FOR_DOT "Error: dot func not defined for unequal" \
                                    " size matrices.\n"
#define INVALID_MATRIX_SIZE_FOR_MULT "Error: * operator not defined for A,B" \
                                     "different #A->cols and #B->rows sizes.\n"
#define FAILED_READ_FILE "Error: Failed to read the file to the matrix.\n"
#define INVALID_MATRIX_SIZE_FOR_ADD "Error: +/+= operator not defined for " \
                                    "unequal size matrices.\n"
#define OUR_OF_RANGE_INDICES "Error: for m(i,j) - i,j must be in range of " \
                             "[0,#rows], [0,#cols] respectively.\n"
#define OUT_OF_RANGE_SLICING "Error: for m[i] - i must be in range of " \
                             "[0,#row * #cols].\n"

/**
 * Matrix generic constructor
 * @param rows new matrix rows-size
 * @param cols new matrix cols-size
 */
Matrix::Matrix (int rows, int cols) : _rows(rows), _cols(cols), _vec_size
(rows*cols), _vec(new float[_vec_size]())
{
  if (rows <= 0 || cols <= 0)
    {
      std::cerr << INVALID_ROWS_COLS_NUM_ERROR << std::endl;
      exit (EXIT_FAILURE);
    }
}

/**
 * Matrix default-constructor
 */
Matrix::Matrix () : Matrix(DEFAULT_ROW_NUM, DEFAULT_COL_NUM) {}

/**
 * Matrix copy-constructor
 * @param oth the copied matrix
 */
Matrix::Matrix (const Matrix &oth) : _rows (oth._rows), _cols (oth._cols)
{
  _vec_size = _rows * _cols;
  _vec = new float[_vec_size];

  for (int i = 0; i < _vec_size; i++)
    _vec[i] = oth._vec[i];
}

// Methods & Functions:
/**
 * transpose the matrix
 * @return reference of the matrix after transposed
 */
Matrix &Matrix::transpose ()
{
  float *new_vec = new float[_vec_size];

  // the transpose action:
  for (int i = 0; i < _rows; i++)
    {
      for (int j = 0; j < _cols; j++)
        {
          new_vec[j * _rows + i] = _vec[i * _cols + j];
        }
    }

  delete[] _vec;
  _rows = _cols;
  _cols = _vec_size/_rows;
  _vec = new_vec;
  return *this;
}


/**
 * vectorize the matrix
 * @return reference of the matrix after vectorized
 */
Matrix &Matrix::vectorize ()
{
  _rows *= _cols;
  _cols = DEFAULT_COL_NUM;
  return *this;
}

/**
 * print the matrix
 */
void Matrix::plain_print () const
{
  for (int i = 0; i < _rows; i++)
    {
      for (int j = 0; j < _cols; j++)
        {
          std::cout << _vec[i * _cols + j] << " ";
        }
      std::cout << std::endl;
    }
}

/**
 * dot product of this matrix and another
 * @param rhs another matrix
 * @return new matrix = the dot product
 */
Matrix Matrix::dot (const Matrix &rhs) const
{
  if (this->_rows != rhs._rows || this->_cols != rhs._cols)
    {
      std::cerr << INVALID_MATRIX_SIZE_FOR_DOT << std::endl;
      exit (EXIT_FAILURE);
    }

  Matrix new_mat (this->_rows, this->_cols);
  for (int i = 0; i < this->_vec_size; i++)
    {
      new_mat._vec[i] = this->_vec[i] * rhs._vec[i];
    }
  return new_mat;
}

/**
 * calculate the frobenius norm of the matrix
 * @return the calculation float value
 */
float Matrix::norm () const
{
  float sum = 0.0;
  for (int i = 0; i < this->_vec_size; i++)
    sum += (float) pow (_vec[i], 2);
  return sqrt (sum);
}

/**
 * similarly the '>>' operator, read data from binary file, and fill the
 * matrix.
 * @param is stream of the binary file
 * @param m matrix to fill
 * @return reference to the given stream
 */
std::istream& read_binary_file (std::istream &is, Matrix &m)
{
  if (!is)
    {
      std::cerr << FILE_NOT_OPEN_ERROR << std::endl;
      exit (EXIT_FAILURE);
    }
  is.seekg (0, std::istream::end);
  int n_bytes = is.tellg ();
  is.seekg (0, std::istream::beg);
  if (n_bytes != (int) sizeof (float) * m._rows * m._cols)
    {
      std::cerr << BYTES_NUM_NOT_SUIT_MATRIX_ERROR << std::endl;
      exit (EXIT_FAILURE);
    }
  is.read ((char *) m._vec, n_bytes);
  if (!is)
    {
      std::cerr << FAILED_READ_FILE << std::endl;
      exit (EXIT_FAILURE);
    }
  return is;
}

// operators:
/**
 * the '+' operator
 * @param rhs another matrix
 * @return new matrix = this + rhs
 */
Matrix Matrix::operator+ (const Matrix &rhs) const
{
  if (this->_rows != rhs._rows || this->_cols != rhs._cols)
    {
      std::cerr << INVALID_MATRIX_SIZE_FOR_ADD << std::endl;
      exit (EXIT_FAILURE);
    }
  Matrix new_mat (_rows, _cols);
  for (int i = 0; i < new_mat._vec_size; i++)
    new_mat._vec[i] = this->_vec[i] + rhs._vec[i];
  return new_mat;
}

/**
 * the '=' operator, update this matrix to be a copy of rhs
 * @param rhs another matrix
 * @return reference of the updated matrix
 */
Matrix &Matrix::operator= (const Matrix &rhs)
{
  if (this == &rhs)
    {
      return *this;
    }
  this->_rows = rhs._rows;
  this->_cols = rhs._cols;
  this->_vec_size = rhs._vec_size;

  delete[] this->_vec;
  _vec = new float[_vec_size];
  for (int i = 0; i < this->_vec_size; i++)
    this->_vec[i] = rhs._vec[i];
  return *this;
}

/**
 * the '*' operator perform the product of this matrix and another
 * @param rhs another matrix
 * @return new matrix = this * rhs
 */
Matrix Matrix::operator* (const Matrix &rhs) const
{
  if (this->_cols != rhs._rows)
    {
      std::cerr << INVALID_MATRIX_SIZE_FOR_MULT << std::endl;
      exit (EXIT_FAILURE);
    }

  Matrix new_mat (this->_rows, rhs._cols);
  for (int i = 0; i < this->_rows; i++)
    {
      for (int j = 0; j < rhs._cols; j++)
        {
          // inner product of (this-> i row, rhs -> j col)
          for (int k = 0; k < this->_cols; k++)
            {
              float a_i_k = (*this) (i, k);
              float b_k_j = rhs (k, j);
              new_mat (i, j) += (a_i_k * b_k_j);
            }
        }
    }
  return new_mat;
}

/**
 * this '*' operator perform the product from *right* of this, by a float
 * number
 * @param scalar float to multiply
 * @return new matrix = this * scalar
 */
Matrix Matrix::operator* (const float &scalar) const
{
  Matrix new_mat (*this);
  for (int i = 0; i < new_mat._vec_size; i++)
    new_mat[i] *= scalar;
  return new_mat;
}

/**
 * this '*' operator perform the product from *left* of a given matrix, by
 * float number
 * @param scalar float to multiply
 * @param m a given matrix
 * @return new matrix = scalar * m
 */
Matrix operator* (const float &scalar, const Matrix &m)
{
  Matrix new_mat (m);
  for (int i = 0; i < new_mat._vec_size; i++)
    new_mat[i] *= scalar;
  return new_mat;
}

/**
 * this '+=' operator add another matrix to this matrix by: this = this + rhs
 * @param rhs another matrix
 * @return reference to this updated matrix, after the += calculation
 */
Matrix &Matrix::operator+= (const Matrix &rhs)
{
  if (this->_rows != rhs._rows || this->_cols != rhs._cols)
    {
      std::cerr << INVALID_MATRIX_SIZE_FOR_ADD << std::endl;
      exit (EXIT_FAILURE);
    }

  for (int i = 0; i < this->_vec_size; i++)
    (*this)[i] += rhs[i];
  return *this;
}

/**
 * the matrix(i,j) operator returns the value in the i,j cell of this matrix
 * @param i index symbolize the row number
 * @param j index symbolize the col number
 * @return a reference to the asked cell in the array
 */
float &Matrix::operator() (const int &i, const int &j)
{
  if (i < 0 || i >= _rows || j < 0 || j >= _cols)
    {
      std::cerr << OUR_OF_RANGE_INDICES << std::endl;
      exit (EXIT_FAILURE);
    }
  return _vec[i * _cols + j];
}

/**
 * this matrix(i,j) operator
 * @param i index symbolize the row number
 * @param j index symbolize the col number
 * @return a value of the (i,j) cell in this matrix
 */
float Matrix::operator() (const int &i, const int &j) const
{
  if (i < 0 || i >= _rows || j < 0 || j >= _cols)
    {
      std::cerr << OUR_OF_RANGE_INDICES << std::endl;
      exit (EXIT_FAILURE);
    }
  return _vec[i * _cols + j];
}

/**
 * this matrix[i] operator
 * @param i index symbolize the i cell in the matrix
 * @return a reference to the [i] cell in this matrix
 */
float &Matrix::operator[] (const int &i)
{
  if (i < 0 || i >= _rows*_cols)
    {
      std::cerr << OUT_OF_RANGE_SLICING << std::endl;
      exit (EXIT_FAILURE);
    }
  return _vec[i];
}

/**
 * this matrix[i] operator
 * @param i index symbolize the i cell in the matrix
 * @return a value of the [i] cell in this matrix
 */
float Matrix::operator[] (const int &i) const
{
  if (i < 0 || i >= _rows*_cols)
    {
      std::cerr << OUT_OF_RANGE_SLICING << std::endl;
      exit (EXIT_FAILURE);
    }
  return _vec[i];
}
/**
 * create a stream of the image represented by a given matrix
 * @param os output stream
 * @param m given Matrix
 * @return a reference to the given stream after filled with matrix details
 */
std::ostream &operator<< (std::ostream &os, const Matrix &m)
{
  for (int i = 0; i < m._rows; i++)
    {
      for (int j = 0; j < m._cols; j++)
        {
          if (m._vec[i * m._cols + j] >= PRINT_IMAGE_FACTOR_VALUE)
            os << "  ";
          else
            os << "**";
        }
      os << std::endl;
    }
  return os;
}


