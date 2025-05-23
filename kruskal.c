#include<stdio.h>

#include <stdlib.h>

// ================================
// Structures
// ================================

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    struct Edge* edge;
};

struct Subset {
    int parent;
    int rank;
};

// ================================
// Function Declarations
// ================================


void printWelcomeMessage();

