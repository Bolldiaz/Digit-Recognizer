#include "Activation.h"
#include <cmath>

#define INVALID_ACTIVATION_TYPE "Error: Invalid Activation_type, must be " \
                                "RELU/SOFTMAX.\n"

/**
 * the relu function, perform the relu operation on a given matrix
 * @param m a given matrix
 * @return new matrix = relu(m)
 */
Matrix Activation::relu (const Matrix &m)
{
  Matrix new_mat (m);
  int vec_size = new_mat.get_cols() * new_mat.get_rows();
  for (int i = 0; i < vec_size; i++)
    if (new_mat[i] < 0)
      new_mat[i] = 0;
  return new_mat;
}

/**
 * the softmax function, perform the softmax operation on a given matrix
 * @param m a given matrix
 * @return new matrix = softmax(m)
 */
Matrix Activation::softmax (const Matrix &m)
{
  Matrix new_mat = Matrix(m);
  int vec_size = new_mat.get_cols() * new_mat.get_rows();
  float sum = 0;
  for (int i = 0; i < vec_size; i++)
    {
      float exp_val = std::exp (new_mat[i]);
      new_mat[i] = exp_val;
      sum += exp_val;
    }
  float factor = 1 / sum;
  return new_mat * factor;
}

/**
 * the Activation constructor
 * @param act_type holds the enum: RELU/SOFTMAX
 */
Activation::Activation (ActivationType act_type)
{
  if (act_type != RELU && act_type != SOFTMAX)
    {
      std::cerr << INVALID_ACTIVATION_TYPE << std::endl;
      exit (EXIT_FAILURE);
    }
  _act_type = act_type;
}

/**
 * activates one of the ActivationType functions: RELU/SOFTMAX on a given
 * matrix
 * @param m a given matrix
 * @return new matrix = relu/softmax(m)
 */
Matrix Activation::operator() (const Matrix &m) const
{
  if (_act_type == RELU)
    return relu(m);
  return softmax(m);
}
