#include "MlpNetwork.h"

/**
 * the MlNetwork regular-constructor
 * @param weights array of the network's weight matrices
 * @param biases array of the network's biases matrices
 */
MlpNetwork::MlpNetwork (Matrix *weights, Matrix *biases) : _weights(weights)
                                                          , _biases(biases) {}

/**
 * the MlpNetwork operator, compute the network manipulations on the given
 * Matrix
 * @param m the input matrix
 * @return a digit struct, contain the values and its distributions
 */
digit MlpNetwork::operator() (Matrix &m)
{
  // creating the output vector:
  for (int i=0 ; i < MLP_SIZE; i++)
    {
      ActivationType act_type = i < MLP_SIZE-1 ? RELU : SOFTMAX;
      Dense cur_dense(this->_weights[i], this->_biases[i], act_type);
      m = cur_dense(m);

    }

  // export the final solution:
  unsigned int value;
  float best_probability = 0;
  for (int i=0; i < m.get_rows() * m.get_cols(); i++)
    {
      if (m[i] > best_probability)
        {
          best_probability = m[i];
          value = i;
        }
    }
  digit d = {value, best_probability};
  return d;
}

