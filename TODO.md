# Table of Contents

1.  [Genotype Implementation](#org263fef9)
        1.  [Informations](#org499a742)
2.  [Representation of neural network](#org52ec607)
    1.  [Find a way to make the propagation of informations efficient](#org0665d9f)
3.  [Crossover Implementation](#orgd8cf9f9)
4.  [Mutation Implementation](#org10e70ae)
        1.  [Weight modification](#org21682a8)
    1.  [Find more informations about weight mutations](#org7bd3537)
        1.  [Add connection mutation](#orgfa1e275)
        2.  [Add node mutation](#orgd218ae1)
5.  [Save Neural Network informations](#orgbdf7f55)
6.  [Define input and output](#org52deb85)
        1.  [Which value to each grid statue](#org997d920)
        2.  [Utils](#org9a14664)


<a id="org263fef9"></a>

# DONE Genotype Implementation


<a id="org499a742"></a>

### Informations

The genotype is the structure that represent a neural network. It can be viewed as a list of genes (Either sensor genes, hidden genes or output genes) and a list of connections between thoses genes.
Each gene can be represented by a number and a tag. The tag "sensor" means that is is a gene from the input layer, the tag "hidden" means that it is a gene from an hidden layer and the tag "ouput" means that it it a gene from the output layer.
A gene connection have 5 attributes : the input gene and the ouput gene (so the neural network is just an oriented graph), the weight of the gene (from 0 to 1, floating number),
if the connection is enabled or not (a connection disabled means that the genes are no longer connected, but they might be connected again in the future) and an innovation number


<a id="org52ec607"></a>

# TODO Representation of neural network

A genotype will represent a neural network.


<a id="org0665d9f"></a>

## TODO Find a way to make the propagation of informations efficient


<a id="orgd8cf9f9"></a>

# DONE Crossover Implementation

The genes connections with the same innovation number are lined up.
Genes that does not match are either disjoint or excess.
Then, the offspring is mades of connections that are randomly choosed between the parents.
Disabled genes may be enabled in future generations.
Disjoint and excess genes can also be inherited randomly.


<a id="org10e70ae"></a>

# TODO Mutation Implementation


<a id="org21682a8"></a>

### Weight modification

Each connection can be either perturbed or not


<a id="org7bd3537"></a>

## DONE Find more informations about weight mutations

> Our mutation operators operated on a single network and would select a random weight and either:
>
> -   completely replace it with a new random value
> -   change the weight by some percentage. (multiply the weight by some random number between 0 and 2 - practically speaking we would tend to constrain that a bit and multiply it by a random number between 0.5 and 1.5. This has the effect of scaling the weight so that it doesn't change as radically. You could also do this kind of operation by scaling all the weights of a particular neuron.
> -   add or subtract a random number between 0 and 1 to/from the weight.
> -   Change the sign of a weight.
> -   swap weights on a single neuron.
>
> You can certainly get creative with mutation operators, you may discover something that works better for your particular problem.
> &#x2013; stackoverflow


<a id="orgfa1e275"></a>

### Add connection mutation

A new connection is made between two unconnected nodes. The weight is set to random. The innovation number is set to $max_{innov\_number} +1$


<a id="orgd218ae1"></a>

### Add node mutation

An old connection is split.
The old connection is disabled and two new connections are added to the genome. The new connection leading into the new node receive a weight of 1, and the new connection leading into the new node receive the old weight.
The innov number of the first connection is set to max<sub>innov</sub> + 1, and the innov number of the second connection is set to max<sub>innov</sub>+2.


<a id="orgbdf7f55"></a>

# TODO Save Neural Network informations

Just serialize the structure


<a id="org52deb85"></a>

# TODO Define input and output

Input : The grid


<a id="org997d920"></a>

### TODO Which value to each grid statue

Ouput : Moves
Orientation of the head


<a id="org9a14664"></a>

### Utils

1.  Values of the grid :

    -   -1 : Empty
    -   -0.5: Apple
    -   0.5: Body
    -   1: Head

2.  Values of the orientation

    -1: Right
    -0.5: Left
    0.5: Up
    1: Down
    0.7x - 1.05
