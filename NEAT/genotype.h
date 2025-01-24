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
  int output;
  float weight;
  int disabled;
  int innov;
} connection;

typedef struct
{
  unsigned int input_n;
  unsigned int output_n;
  unsigned int connection_n;
  unsigned int node_n;
  int max_innov;
  connection* genes_connections;
  enum state* genes_states;
  int score;
} NN;

typedef struct
{
  float weightModif;
  float uniformPerturbation;
  float newNode;
  float newConnection;
} percentages;

/**
 @brief Init and return an empty neural network with n input and n output
 @param input_n number of input genes
 @param output_n number of output genes
 @retval NN An empty NN
*/
NN* initEmptyNN(int input_n, int output_n);
void deleteNN(NN* nn);
NN* crossover(NN* parent1, NN* parent2, float disabledPercentage);
void mutation(NN* nn, percentages* p);
connection initConnection(int input, int output, float weight, int disabled, int innov);
#endif
