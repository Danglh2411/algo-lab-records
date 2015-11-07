/* Dijkstra's shortest Path Algorithm
 *
 * Submitted by : Himanshu Mishra
 * Roll No. : 14MA20014
 */

#define NIL 0

#define BLACK 0
#define WHITE 1

#define INFINITE INT_MAX

#define MAX_SIZE 100

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "limits.h"

struct Graph {
    int V;
    int **adjMatrix;
    int *costArray;
    int *parentArray;
    int *colorArray;
};

void printGraph(struct Graph* G) {
    int i;
    printf("The Cost Matrix :\n");
    for(i=1; i<=G->V; i++) {
        printf(" %d ", G->costArray[i]);
    }
    printf("\n");
    printf("The Parent Matrix :\n");
    for(i=1; i<=G->V; i++) {
        printf(" %d ", G->parentArray[i]);
    }
    printf("\n");
}

// A Queue data structure
struct Queue {
    int arr[MAX_SIZE];
    int length;
    int head;
    int tail;
};

void ENQUEUE(struct Queue* Q, int s) {
    Q->arr[Q->tail] = s;
    if (Q->tail==Q->length) {
        Q->tail = 0;
    }
    else
        ++(Q->tail);
}

int DEQUEUE(struct Queue* Q) {
    int to_return;
    to_return = Q->arr[Q->head];
    if (Q->head==Q->length) {
        Q->head = 0;
    }
    else
        ++(Q->head);
    return to_return;
}

void dijkstra(struct Graph *G, int s) {
    struct Queue* Q;
    Q = (struct Queue*)malloc(sizeof(struct Queue));
    Q->length = MAX_SIZE - 1;
    Q->head = Q->tail = 0;

    int i, j;
    G->costArray[s] = 0;

    ENQUEUE(Q, s);

    while(Q->head!=Q->tail) {      
        j = DEQUEUE(Q);
        G->colorArray[j] = BLACK;
        for (i=1; i<=G->V; i++) {
            if (G->adjMatrix[i][j]==0) {continue;} // Not j's neighbors
            else {
                if (G->colorArray[i]!=BLACK) { // Not j's parent
                    if (G->costArray[i]==INFINITE) { // New node
                        G->costArray[i] = G->costArray[j] + G->adjMatrix[i][j];
                        G->parentArray[i] = j;
                    }
                    else if (G->costArray[i] > G->costArray[j] + G->adjMatrix[i][j]) { // Updated node
                        G->costArray[i] = G->costArray[j] + G->adjMatrix[i][j];
                        G->parentArray[i] = j;
                    }
                    ENQUEUE(Q, i);
                }
            }
        }
    }
}
    


int main() {
    int i, j;
    
    struct Graph* G;
    G = (struct Graph*)malloc(sizeof(struct Graph));

    printf("Enter the number of nodes : \n");
    scanf("%d", &G->V);

    // Allocate memory for Matrices
    G->adjMatrix = (int **)malloc((G->V + 1)*sizeof(int *));
    G->costArray = (int *)malloc((G->V + 1)*sizeof(int));
    G->parentArray = (int *)malloc((G->V + 1)*sizeof(int));
    G->colorArray = (int *)malloc((G->V + 1)*sizeof(int));
    for(i=0; i<=G->V+1; i++) {
        G->adjMatrix[i] = (int *)malloc((G->V + 1)*sizeof(int));
    }

    // Initialize the Graph
    for (i=0; i<=G->V; i++) {
        for (j=0; j<=G->V; j++) {
            G->adjMatrix[i][j] = 0;
        }
    }

    // Add weight and edges
    printf("Enter the pair of nodes to add Edge and also the weight :\n");
    printf("(Enter (0, 0, 0) to terminate)\n");
    int node1, node2, weight;
    while(true) {
        scanf("%d %d %d", &node1, &node2, &weight);
        if (node1==0 || node2==0) {break;}
        else if (weight<=0) {
            printf("Weight must be positive!\n");
            break;
        }
        else {
            G->adjMatrix[node1][node2] = weight;
            G->adjMatrix[node2][node1] = weight;
        }
    }

    // Run Dijkstra as all the nodes as starting nodes
    // Initialize Graph
    for (i=1; i<=G->V; ++i) {
        G->parentArray[i] = 0;
        G->costArray[i] = INFINITE;
        G->colorArray[i] = WHITE;
    }
    printf("Enter the node to start traversal from :\n");
    int s;
    scanf("%d", &s);
    dijkstra(G, s);

    printGraph(G);
}
