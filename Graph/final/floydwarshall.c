#define NIL 0
#define INFINITE 99999

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct Graph {
    int V;
    int **adjMatrix;
    int **costMatrix;
    int **nextMatrix;
};

void generatePath(struct Graph* G, int u, int v) {
    if (G->nextMatrix[u][v]==0) {
        printf("No path from %d to %d.\n", u, v);
    }
    else {
        printf("%d", u);
        while(u!=v) {
            u = G->nextMatrix[u][v];
            printf("-> %d", u);
        }
    }
}

void printGraph(struct Graph* G) {
    int i, j;
    printf("The cost matrix :\n");
    for (i=1; i<=G->V; i++) {
        for (j=1; j<=G->V; j++) {
            printf("%d ", G->costMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("The Parent Matrix :\n");
    for (i=1; i<=G->V; i++) {
        for (j=1; j<=G->V; j++) {
            printf("%d ", G->nextMatrix[i][j]);
        }
        printf("\n");
    }
}

void floydwarshall(struct Graph* G) {
    int i, j, k;

    // Replace 0 with INFINITE where there is no connection
    for (i=1; i<=G->V; i++) {
        for (j=1; j<=G->V; j++) {
            if (i!=j && G->adjMatrix[i][j]==0) {
                G->adjMatrix[i][j] = INFINITE;
            }
        }
    }

    // For every edge update cost and parent matrix
    for (i=1; i<=G->V; i++) {
        for (j=1; j<=G->V; j++) {
            if (G->adjMatrix[i][j]!=0) {
                G->costMatrix[i][j] = G->adjMatrix[i][j];
                G->nextMatrix[i][j] = j;
            }
        }
    }

    for (k=1; k<=G->V; k++) {
        for (i=1; i<=G->V; i++) {
            for (j=1; j<=G->V; j++) {
                if (G->adjMatrix[i][k]!=0 && G->adjMatrix[k][j]!=0) {
                    if (G->costMatrix[i][j] > G->costMatrix[i][k] + G->costMatrix[k][j]) {
                        G->costMatrix[i][j] = G->costMatrix[i][k] + G->costMatrix[k][j];
                        G->nextMatrix[i][j] = G->nextMatrix[i][k];
                    }
                }
            }
        }
    }

}

int main()
{
    int i,j; // Loop iterators

    struct Graph* G;
    G = (struct Graph *)malloc(sizeof(struct Graph));

    // Take the number of nodes
    printf("Enter the number of nodes :\n");
    scanf("%d", &G->V);

    // Allocate space to the matrices
    G->adjMatrix = (int **)malloc((G->V + 1)*sizeof(int *));
    G->costMatrix = (int **)malloc((G->V + 1)*sizeof(int *));
    G->nextMatrix = (int **)malloc((G->V + 1)*sizeof(int *));
    for (i=1; i<=G->V; i++) {
        G->adjMatrix[i] = (int *)malloc((G->V + 1)*sizeof(int));
        G->costMatrix[i] = (int *)malloc((G->V + 1)*sizeof(int));
        G->nextMatrix[i] = (int *)malloc((G->V + 1)*sizeof(int));
    }

    // Take the adjacency matrix as input
    printf("Give the adjacency matrix of the Graph :\n");
    for (i=1; i<=G->V; i++) {
        for (j=1; j<=G->V; j++) {
            scanf("%d", &G->adjMatrix[i][j]);
        }
    }

    // Initialize
    for (i=1; i<=G->V; i++) {
        for (j=1; j<=G->V; j++) {
            G->nextMatrix[i][j] = NIL;
            G->costMatrix[i][j] = 0;
        }
    }

    floydwarshall(G);
}
