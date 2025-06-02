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

int main() {
    printWelcomeMessage();
    explainKruskal();
    waitForUser();

    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));

    printf("\nEnter the number of vertices in the graph: ");
    while (scanf("%d", &graph->V) != 1 || graph->V <= 0) {
        printf("Invalid inputis not allowed. Please enter a positive integer: ");
        while (getchar() != '\n');
    }

    printf("Enter the number of edges in the graph: ");
    while (scanf("%d", &graph->E) != 1 || graph->E <= 0) {
        printf("Invalid input. Please enter a positive integer: ");
        while (getchar() != '\n');
    }

    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));

    inputGraph(graph);

    printf("\nYou entered the following graph:\n");
    displayGraph(graph);



    graphSummary(graph);
    waitForUser();

    printf("\nApplying Kruskal's Algorithm...\n\n");
    KruskalMST(graph);

    free(graph->edge);
    free(graph);

    printf("\nThank you for using the Kruskal's Algorithm program!\n");
    printf("Exiting...\n");
    return 0;
}

// ================================
// Welcome and Instructional Content
// ================================

void printWelcomeMessage() {
    printf("=========================================\n");
    printf("   Kruskal's Algorithm in C - Ver. 1.1   \n");
    printf("=========================================\n");
    printf("         Author: YourNameHere            \n");
    printf("=========================================\n");
}

void printMenu() {
    printf("\nMenu:\n");
    printf("1. Enter Graph\n");
    printf("2. Display Graph\n");
    printf("3. Run Kruskal's Algorithm\n");
    printf("4. Exit\n");
}

void explainKruskal() {
    printf("\nKruskal's Algorithm is a Greedy algorithm used to find the Minimum Spanning Tree (MST) of a graph.\n");
    printf("It works as follows:\n");
    printf("1. Sort all the edges in non-decreasing order of their weight.\n");
    printf("2. Pick the smallest edge. Check if it forms a cycle using Union-Find.\n");
    printf("3. If it doesn't form a cycle, include it in the MST.\n");
    printf("4. Repeat until the MST contains (V - 1) edges.\n");
}

void waitForUser() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

void graphSummary(struct Graph* graph) {
    printf("\n====================================\n");
    printf("           Graph Summary            \n");
    printf("====================================\n");
    printf("Number of Vertices: %d\n", graph->V);
    printf("Number of Edges   : %d\n", graph->E);
    printf("Edge List Format  : Source -- Destination == Weight\n");
    printf("====================================\n");
}

// ================================
// Graph Input and Display
// ================================

void inputGraph(struct Graph* graph) {
    for (int i = 0; i < graph->E; i++) {
        int src, dest, weight;

        printf("Enter edge %d (src dest weight): ", i + 1);
        while (scanf("%d %d %d", &src, &dest, &weight) != 3 || src < 0 || dest < 0 || weight < 0 || src >= graph->V || dest >= graph->V) {
            printf("Invalid input. Please enter valid integers (src[0-%d] dest[0-%d] weight>0): ", graph->V - 1, graph->V - 1);
            while (getchar() != '\n');
        }

        graph->edge[i].src = src;
        graph->edge[i].dest = dest;
        graph->edge[i].weight = weight;
    }
}

void displayGraph(struct Graph* graph) {
    printf("Vertices: %d, Edges: %d\n", graph->V, graph->E);
    for (int i = 0; i < graph->E; i++) {
        printf("Edge %d: %d -- %d == %d\n", i + 1, graph->edge[i].src, graph->edge[i].dest, graph->edge[i].weight);
    }
}

// ================================
// Kruskal's Algorithm Functions
// ================================

int compareEdges(const void* a, const void* b) {
    struct Edge* e1 = (struct Edge*) a;
    struct Edge* e2 = (struct Edge*) b;
    return e1->weight - e2->weight;
}

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        printf("find: Path compression for vertex %d\n", i);
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    printf("find: Returning root of %d -> %d\n", i, subsets[i].parent);
    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    printf("Union: xroot = %d, yroot = %d\n", xroot, yroot);

    if (xroot == yroot) {
        printf("Union: Already in the same set. No action taken.\n");
        return;
    }

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
        printf("Union: %d becomes child of %d\n", xroot, yroot);
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
        printf("Union: %d becomes child of %d\n", yroot, xroot);
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
        printf("Union: %d becomes child of %d and rank increased\n", yroot, xroot);
    }
}

void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compareEdges);

    printf("Edges sorted by weight:\n");
    for (int j = 0; j < graph->E; j++) {
        printf("%d -- %d == %d\n", graph->edge[j].src, graph->edge[j].dest, graph->edge[j].weight);
    }

    struct Subset* subsets = (struct Subset*) malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edge[i++];
        printf("\nConsidering edge: %d -- %d == %d\n", next_edge.src, next_edge.dest, next_edge.weight);

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            printf("No cycle detected. Adding edge to MST.\n");
            result[e++] = next_edge;
            Union(subsets, x, y);
        } else {
            printf("Cycle detected. Skipping edge.\n");
        }
    }

    printMST(result, e);
    free(subsets);
}

void printMST(struct Edge result[], int e) {
    int totalWeight = 0;
    printf("\n====================================\n");
    printf("        Minimum Spanning Tree       \n");
    printf("====================================\n");
    for (int i = 0; i < e; ++i) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("====================================\n");
    printf("Total weight of MST: %d\n", totalWeight);
}
pulling 
