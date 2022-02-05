#ifndef C___PROJECT_DENSE_H
#define C___PROJECT_DENSE_H

#include "Activation.h"

class Dense
{
  Matrix _w, _bias;
  Activation _act;

 public:
/**
 * the Dense constructor
 * @param w the Dense weight matrix
 * @param bias the Dense bias matrix
 * @param act_type the Dense Activation-function-type
 */
  Dense(const Matrix &w, const Matrix &bias, ActivationType act_type);

// Getters:
/**
 * the Dense weight-field getter
 * @return the weight matrix
 */
  const Matrix& get_weights () const;

/**
 * the Dense bias-field getter
 * @return the bias matrix
 */
  const Matrix& get_bias () const;

/**
 * the Dense Activation-field getter
 * @return the Activation
 */
  const Activation& get_activation() const;

/**
 * the Dense operator, perform the Dense manipulations on a given matrix
 * @param m a given matrix
 * @return the Dense manipulations output-matrix-result
 */
  Matrix operator() (const Matrix &m) const;
};

#endif //C___PROJECT_DENSE_H
