#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct Graph {
    int V;
    int **adjMatrix;
};

void printGraph(struct Graph* G) {
    int i, j;
    for(i=1; i<=G->V; i++) {
        for(j=1; j<=G->V; j++) {
            printf("%d\t", G->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void prim(struct Graph* G, int **primset) {
    int i, j, min_weight, min_weighted_node1, min_weighted_node2;

    int e_picked; // Edges picked
    e_picked = 0;

    bool n_picked[G->V + 1], n_newly_picked[G->V + 1]; // Nodes picked
    for (i=1; i<=G->V; i++) {
        n_picked[i] = false;
        n_newly_picked[i] = false;
    }

    // Let's start with node 1
    n_picked[1] = true;
    
    for(e_picked=0; e_picked<G->V - 1; e_picked++) {
        // Update n_picked with n_newly_picked
        for (i=1; i<=G->V; i++) {
            if(n_newly_picked[i]==true) {
                n_picked[i] = true;
                n_newly_picked[i] = false;
            }
        }
        min_weight = INT_MAX;
        for (i=1; i<=G->V; i++) {
            // Only the picked nodes    
            if(n_picked[i]) {
                // Finding the minimum weighted edge
                for(j=1; j<=G->V; j++) {
                    if(G->adjMatrix[i][j]!=INT_MAX && // If there's an edge
                            !n_picked[j] && // And the edge is not picked
                            j!=i) { // And j is not i itself
                        if(G->adjMatrix[i][j]<min_weight) {
                                min_weight = G->adjMatrix[i][j];
                                min_weighted_node1 = i;
                                min_weighted_node2 = j;
                            }
                        }
                    }
                    primset[e_picked + 1][0] = min_weighted_node1;
                    primset[e_picked + 1][1] = min_weighted_node2;
                    primset[e_picked + 1][2] = min_weight;
                    n_newly_picked[min_weighted_node2] = true;
                }
            }
    }
}

int main ()
{
    int i,j; // Loop iterators

    struct Graph* G;
    G = (struct Graph *)malloc(sizeof(struct Graph));

    // Take the number of nodes
    printf("Enter the number of nodes :\n");
    scanf("%d", &G->V);

    // V-1 edges will be there in the MST
    // primset is a set of those edges and their weights
    int **primset;
    primset = (int **)malloc((G->V)*sizeof(int *));
    for (i=1; i<=G->V; i++) {
        primset[i] = (int *)malloc(3*sizeof(int));
    }

    // Allocate space to the adjacency matrix
    G->adjMatrix = (int **)malloc((G->V + 1)*sizeof(int *));
    for (i=1; i<=G->V; i++) {
        G->adjMatrix[i] = (int *)malloc((G->V + 1)*sizeof(int));
    }

    // Take the adjacency matrix as input
    printf("Give the adjacency matrix of the Graph :\n");
    for (i=1; i<=G->V; i++) {
        for (j=1; j<=G->V; j++) {
            scanf("%d", &G->adjMatrix[i][j]);
            if (G->adjMatrix[i][j]==0) {G->adjMatrix[i][j]=INT_MAX;} // Putting infinite weight
        }
    }

    // printGraph(G);
    prim(G, primset);

    // Print primset
    for (i=1; i<G->V; i++) {
        printf("Edge %d :\t", i);
        for (j=0; j<3; j++) {
            printf("%d\t", primset[i][j]);
        }
        printf("\n");
    }
}
