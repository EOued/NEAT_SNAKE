#ifndef GENOTYPE_H
#define GENOTYPE_H

enum state
{
  input,
  output,
  hidden
};
typedef struct
{
  int input;
  enum state inputState;
  int output;
  enum state outputState;
  float weight;
  int disabled;
  int innov;
} connection;

typedef struct
{
  unsigned int input_n;
  unsigned int output_n;
  unsigned int connection_n;
  connection* genes_connections;
  int score;
} NN;

/**
 @brief Init and return an empty neural network with n input and n output
 @param input_n number of input genes
 @param output_n number of output genes
 @retval NN An empty NN
*/
NN* initEmptyNN(int input_n, int output_n);
void deleteNN(NN* nn);
NN* crossover(NN* parent1, NN* parent2);
NN* mutation(NN* nn);
#endif
