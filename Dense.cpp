#include "Dense.h"

#define INVALID_ACTIVATION_TYPE "Error: Invalid Activation_type, must be " \
                                "RELU/SOFTMAX.\n"


/**
 * the Dense constructor
 * @param w the Dense weight matrix
 * @param bias the Dense bias matrix
 * @param act_type the Dense Activation-function-type
 */
Dense::Dense (const Matrix &w, const Matrix &bias, ActivationType
act_type): _w(w), _bias(bias), _act(act_type)
{
  if (act_type != RELU && act_type != SOFTMAX)
    {
      std::cerr << INVALID_ACTIVATION_TYPE << std::endl;
      exit (EXIT_FAILURE);
    }
}

// Getters:
/**
 * the Dense weight-field getter
 * @return the weight matrix
 */
const Matrix& Dense::get_weights () const
{
  return _w;
}

/**
 * the Dense bias-field getter
 * @return the bias matrix
 */
const Matrix& Dense::get_bias () const
{
  return _bias;
}

/**
 * the Dense Activation-field getter
 * @return the Activation
 */
const Activation& Dense::get_activation () const
{
  return _act;
}

/**
 * the Dense operator, perform the Dense manipulations on a given matrix
 * @param m a given matrix
 * @return the Dense manipulations output-matrix-result
 */
Matrix Dense::operator() (const Matrix &m) const
{
  return _act((_w * m) += _bias);
}
