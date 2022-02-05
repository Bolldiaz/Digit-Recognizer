//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Digit.h"
#include "Dense.h"

#define MLP_SIZE 4

//
const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64, 128},
                                    {20, 64},
                                    {10, 20}};
const matrix_dims bias_dims[]    = {{128, 1},
                                    {64, 1},
                                    {20, 1},
                                    {10, 1}};

class MlpNetwork
{
  Matrix *_weights, *_biases;

 public:
/**
 * the MlpNetwork regular-constructor
 * @param weights array of the network's weight matrices
 * @param biases array of the network's biases matrices
 */
  MlpNetwork(Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE]);

/**
 * the MlpNetwork operator, compute the network manipulations on the given
 * Matrix
 * @param m the input matrix
 * @return a digit struct, contain the values and its distributions
 */
  digit operator() (Matrix &m);

};

#endif // MLPNETWORK_H
