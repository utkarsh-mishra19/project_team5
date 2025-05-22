
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
void printMenu();
void inputGraph(struct Graph* graph);
void displayGraph(struct Graph* graph);
void explainKruskal();
void waitForUser();
void graphSummary(struct Graph* graph);

int compareEdges(const void* a, const void* b);
int find(struct Subset subsets[], int i);
void Union(struct Subset subsets[], int x, int y);
void KruskalMST(struct Graph* graph);
void printMST(struct Edge result[], int e);

// ================================
// Main
// ================================
