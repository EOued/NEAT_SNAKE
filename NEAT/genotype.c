#include "genotype.h"
#include "../UTILS/errors.h"
#include "../UTILS/quicksort.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

NN* initEmptyNN(int input_n, int output_n)
{
  NN* nn;
  if (!(nn = malloc(sizeof(NN))))
    sendError("Can't allocate memory for neural network", 1);
  nn->connection_n      = 0;
  nn->genes_connections = NULL;
  nn->input_n           = input_n;
  nn->output_n          = output_n;
  nn->score             = 0;
  nn->node_n            = input_n + output_n;
  nn->genes_states      = malloc(nn->node_n * sizeof(enum state));
  for (unsigned int i = 0; i < nn->node_n; i++)
    nn->genes_states[i] = i < input_n ? input : output;
  nn->max_innov = -1;
  return nn;
}
void deleteNN(NN* nn)
{
  if (!nn) return;
  if (nn->genes_connections) free(nn->genes_connections);
  if (nn->genes_states) free(nn->genes_states);
  free(nn);
  return;
}

int isGreaterInnov(void* elem1, void* elem2)
{
  connection* c1 = (connection*)elem1;
  connection* c2 = (connection*)elem2;

  return c1->innov > c2->innov;
}
int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

NN* crossover(NN* parent1, NN* parent2, float disabledPercentage)
{
  if (parent1->input_n != parent2->input_n ||
      parent1->output_n != parent2->output_n)
    sendError("Trying to mate two NNs with different input/output nodes values "
              "! Stopping crossover.",
              2);
  // One of the parent is NULL
  if (!parent1->genes_connections && !parent2->genes_connections)
    return parent1;
  if (!parent1->genes_connections) return parent2;
  if (!parent2->genes_connections) return parent1;
  NN* child = initEmptyNN(parent1->input_n, parent1->output_n);
  sort(parent1->genes_connections, isGreaterInnov, sizeof(connection),
       parent1->connection_n);
  sort(parent2->genes_connections, isGreaterInnov, sizeof(connection),
       parent2->connection_n);
  int rdm;
  int p1InnovIndex = 0;
  int p2InnovIndex = 0;
  int p1InnovValue;
  int p2InnovValue;
  int shift = 0;
  int minInnov =
      min(parent1->genes_connections[parent1->connection_n - 1].innov,
          parent2->genes_connections[parent2->connection_n - 1].innov);
  int maxInnov =
      max(parent1->genes_connections[parent1->connection_n - 1].innov,
          parent2->genes_connections[parent2->connection_n - 1].innov);
  child->genes_connections = malloc(maxInnov * sizeof(connection));
  child->connection_n      = 0;
  for (int i = 0; i <= minInnov; i++)
  {
    rdm          = rand() % 2;
    p1InnovValue = parent1->genes_connections[p1InnovIndex].innov;
    p2InnovValue = parent2->genes_connections[p2InnovIndex].innov;
    // The two innov value are not in order : we skip that iteration without
    // changing the increment indexes
    if (p1InnovValue != i && p2InnovValue != i) continue;
    // Disjoint genes
    if (p1InnovValue != p2InnovValue)
    {
      // parent1 is the more fit and it have disjoint genes, so we keep them for
      // the child
      if (parent1->score > parent2->score && p1InnovValue == i)
      {
        child->genes_connections[i - shift] =
            parent1->genes_connections[p1InnovIndex];
        child->connection_n++;
        goto p1leave;
      }
      // parent2 is the more fit and it have disjoint genes, so we keep them for
      // the child
      if (parent2->score > parent1->score && p2InnovValue == i)
      {
        child->genes_connections[i - shift] =
            parent2->genes_connections[p2InnovIndex];
        child->connection_n++;
        goto p2leave;
      }
      // The parents have same fitness : we randomly take (or not) the gene
      if (parent1->score == parent2->score)
      {
        NN* parent = rdm ? parent2 : parent1;
        int innov  = rdm ? p2InnovValue : p1InnovValue;
        int index  = rdm ? p2InnovIndex : p1InnovIndex;
        if (i == innov)
          child->genes_connections[i - shift] =
              parent->genes_connections[index];
        if (rdm) goto p2leave;
        goto p1leave;
        // No genes have been added : we need to shift all futur indexes of 1
        shift++;
        if (p1InnovValue == i) goto p1leave;
        else
          goto p2leave;

      p1leave:
        p1InnovIndex++;
        continue;
      p2leave:
        p2InnovIndex++;
        continue;
      }
    }
    if (rdm == 0)
      child->genes_connections[i - shift] =
          parent1->genes_connections[p1InnovIndex];
    else
      child->genes_connections[i - shift] =
          parent2->genes_connections[p2InnovIndex];
    if (parent1->genes_connections[p1InnovIndex].disabled &&
        parent2->genes_connections[p2InnovIndex].disabled)
    {
      child->genes_connections[i - shift].disabled =
          (rand() % 100 <= (int)(disabledPercentage * 100));
    }

    child->connection_n++;
    p1InnovIndex++;
    p2InnovIndex++;
  }
  // Check for excess genes
  if (maxInnov == minInnov) goto end;
  // There is excess genes
  // Checking fitnesses : if the more fit nn does not have the excess genes, we
  // can skip that part
  if (parent1->score > parent2->score &&
      parent1->genes_connections[parent1->connection_n - 1].innov == minInnov)
    goto end;
  if (parent2->score > parent1->score &&
      parent2->genes_connections[parent2->connection_n - 1].innov == minInnov)
    goto end;
  // Checking fitnesses : if the more fit nn does have excess genes, than we
  // need to add all of them The innovation index of the excess parent is set to
  // the first exces gene
  NN* excessParent =
      parent1->genes_connections[parent1->connection_n - 1].innov == minInnov
          ? parent2
          : parent1;
  int excessIndex = excessParent == parent1 ? p1InnovIndex : p2InnovIndex;
  for (unsigned int i = excessIndex; i < excessParent->connection_n; i++)
  {
    rdm = rand() % 2;
    if ((parent1->score == parent2->score && rdm) ||
        (parent1->score != parent2->score))
      child->genes_connections[child->connection_n++] =
          excessParent->genes_connections[i];
  }

end:
{
  // Calculation of node number and max innovation
  child->node_n    = 0;
  child->max_innov = -1;
  int* seen        = calloc(2 * child->connection_n, sizeof(int));
  for (unsigned int i = 0; i < child->connection_n; i++)
  {
    child->max_innov = max(child->max_innov, child->genes_connections[i].innov);
    if (!seen[child->genes_connections[i].input])
    {
      child->node_n++;
      seen[child->genes_connections[i].input] = 1;
    }
    if (!seen[child->genes_connections[i].output])
    {
      child->node_n++;
      seen[child->genes_connections[i].output] = 1;
    }
  }
  child->genes_states =
      realloc(child->genes_states, child->node_n * sizeof(enum state));
  for (unsigned int i = 0; i < child->node_n; i++)
  {
    child->genes_states[i] = i < parent1->node_n ? parent1->genes_states[i]
                                                 : parent2->genes_states[i];
  }
  return child;
}
}
float rdmFloat(float a) { return ((float)rand() / (float)(RAND_MAX)) * a; }

void mutation(NN* nn, percentages* percentage)
{
  int rdm;
  int rdm2;
  for (unsigned int i = 0; i < nn->connection_n; i++)
  {
    rdm  = rand() % 100;
    rdm2 = rand() % 100;
    if (rdm < percentage->weightModif)
    {
      if (rdm2 < percentage->uniformPerturbation)
        nn->genes_connections[i].weight *= rdmFloat(2);
      else
        nn->genes_connections[i].weight = rdmFloat(1);
    }
  }
  // Adding a node
  rdm = rand() % 100;
  if (nn->connection_n && rdm < percentage->newNode * 100)
  {
    // Selecting a random commection
    rdm2                                 = rand() % nn->connection_n;
    nn->genes_connections[rdm2].disabled = 1;
    nn->genes_connections                = realloc(
        nn->genes_connections, (nn->connection_n + 2) * sizeof(connection));
    nn->genes_connections[nn->connection_n] = initConnection(
        nn->genes_connections[rdm2].input, nn->node_n,
        nn->genes_connections[rdm2].weight, 0, nn->max_innov + 1);
    nn->genes_connections[nn->connection_n + 1] =
        initConnection(nn->node_n, nn->genes_connections[rdm2].output, 1, 0,
                       nn->max_innov + 2);
    nn->connection_n += 2;
    nn->max_innov += 2;
    nn->node_n++;
  }
  // Adding a connection
  rdm = rand() % 100;
  if (rdm < percentage->newConnection * 100)
  {
    int firstNode  = rand() % nn->node_n;
    int secondNode = rand() % nn->node_n;
    if (firstNode == secondNode)
      secondNode += secondNode == nn->node_n - 1 ? -1 : 1;
    nn->genes_connections = realloc(
        nn->genes_connections, (nn->connection_n + 1) * sizeof(connection));
    nn->genes_connections[nn->connection_n++] =
        initConnection(firstNode, secondNode, rdmFloat(1), 0, ++nn->max_innov);
  }
  return;
}

connection initConnection(int input, int output, float weight, int disabled,
                          int innov)
{
  connection c;
  c.input    = input;
  c.output   = output;
  c.weight   = weight;
  c.disabled = disabled;
  c.innov    = innov;
  return c;
}

void printNN(NN* nn)
{
  printf("State of nn:\n");
  printf("\tNumber of input genes : %d\n\tNumber of output genes : %d\n",
         nn->input_n, nn->output_n);
  printf("\tConnections :\n");
  for (unsigned int i = 0; i < nn->connection_n; i++)
  {
    printf("\t\t %sInnov %d :  %d --%.2f--> %d\n",
           nn->genes_connections[i].disabled ? "(DISABLED) " : "\0",
           nn->genes_connections[i].innov, nn->genes_connections[i].input,
           nn->genes_connections[i].weight, nn->genes_connections[i].output);
  }
}

int main()
{
  srand(time(NULL));
  NN* p1 = initEmptyNN(3, 1);
  printNN(p1);
  percentages* p         = malloc(sizeof(percentages));
  p->newConnection       = 1;
  p->newNode             = 0;
  p->uniformPerturbation = 0;
  p->weightModif         = 0;
  mutation(p1, p);
  printNN(p1);
  p->newConnection = 0;
  p->newNode       = 1;
  mutation(p1, p);
  printNN(p1);
  free(p);
  deleteNN(p1);
  return 0;
}
