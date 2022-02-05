//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    RELU,
    SOFTMAX
};

class Activation
{
 private:
  ActivationType _act_type;

/**
 * the relu function, perform the relu operation on a given matrix
 * @param m a given matrix
 * @return new matrix = relu(m)
 */
  static Matrix relu(const Matrix &m);

/**
 * the softmax function, perform the softmax operation on a given matrix
 * @param m a given matrix
 * @return new matrix = softmax(m)
 */
  static Matrix softmax(const Matrix &m);

 public:

/**
 * the Activation constructor
 * @param act_type holds the enum: RELU/SOFTMAX
 */
  Activation(ActivationType act_type);

  // Getter:
  ActivationType get_activation_type () const
  {
    return _act_type;
  }

/**
 * activates one of the ActivationType functions: RELU/SOFTMAX on a given
 * matrix
 * @param m a given matrix
 * @return new matrix = relu/softmax(m)
 */
  Matrix operator() (const Matrix &m) const;
};

#endif //ACTIVATION_H
