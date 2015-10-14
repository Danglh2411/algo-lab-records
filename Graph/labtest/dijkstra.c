/* Dijkstra's shortest Path Algorithm
 *
 * Submitted by : Himanshu Mishra
 * Roll No. : 14MA20014
 */

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define INFINITE INT_MAX 

#define MAX_SIZE 100

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "limits.h"

// Elements of the Adjacency List
struct listNode {
    int node;
    struct listNode *next;
    int weight;
};

// Elements of the array having pointers to the list
struct listArray {
    struct listNode *next;
    int color;
    int weight;  // This is the shortest path weight from the source vertex
};

// The array representing the Graph
struct Graph {
    int V;
    struct listArray *arr;
};

// Function to return a new node for the Adjacency List
struct listNode* newListNode(int node) {
    struct listNode* newListNode;
    newListNode = (struct listNode*)malloc(sizeof(struct listNode));
    newListNode->node = node;

    return newListNode;
}

// Function to add an edge between two nodes
void addEdge(struct Graph* G, int node1, int node2, int weight) {
    struct listNode* newNode = newListNode(node2);
    newNode->weight = weight;
    newNode->next = (G->arr)[node1].next;
    (G->arr)[node1].next = newNode;
}

// Function to print the Adjacency List of the Graph
void printGraph(struct Graph* G) {
    struct listNode* iter;
    printf("The Adjacency List :\n");
    for (int i = 1; i <= G->V; ++i) {
        printf("%d ", i);
        iter = G->arr[i].next;
        while(iter!=NULL) {
            printf("-> %d(%d) ", iter->node, iter->weight);
            iter = iter->next;
        }
        printf("\n weight of an edge is written in braces ().");
    }
}

int edge_weight(struct Graph* G, int u, int v) {
    struct listNode* iter;
    iter = G->arr[u].next;
    while(iter!=NULL) {
        if (iter->node==v)
            return iter->weight;
        else
            iter = iter->next;
    }
}

void dijkstra(struct Graph *G, int s) {
    // Set configurations of all the nodes
    for (int i = 1; i <= G->V; ++i) {
        G->arr[i].color = WHITE;
        G->arr[i].weight = INFINITE;
    }

    // For the root
    G->arr[s].color = GRAY;
    G->arr[s].weight = 0;

    // Do the iteration
    int u, v;
    struct listNode* iter;
    for (u=1; u<=G->V; ++u) {
        iter = G->arr[u].next; 

        while(iter!=NULL) {
            v = iter->node;
            
            if (G->arr[v].color!=BLACK) {
                // Dijkstra hackery
                if (G->arr[v].weight > G->arr[u].weight) {
                    G->arr[v].weight = G->arr[u].weight + edge_weight(G, u, v);
                }
            }
            
            iter = iter->next;
        }
        G->arr[u].color = BLACK;
    }
}

void print_dijkstra(struct Graph* G, int s) {
    printf("Vertex  |  Weight from %d Vertex\n", s);
    for (int i=1; i<=G->V; i++) {
        printf("   %d   ", i);
        printf(" |         %d   \n", G->arr[i].weight);
    }
}

int main(int argc, char const *argv[])
{
    int V;  // The number of nodes
    printf("Enter the number of nodes : \n");
    scanf("%d", &V);

    // Create a Graph G
    struct Graph* G;
    G = (struct Graph*)malloc(sizeof(struct Graph));
    G->V = V;
    // Here the node at index i will have the value i. So, the zeroth index is left empty.
    G->arr = (struct listArray *)malloc((V+1)*sizeof(struct listArray));
    for (int i = 1; i <= G->V; ++i) {
        G->arr[i].next = NULL;
    }

    printf("Enter pair of nodes to add Edge and also the weight :\n");
    printf("(Enter (0, 0, 0) to terminate)\n");
    int node1, node2, weight;
    while(true) {
        scanf("%d %d %d", &node1, &node2, &weight);
        if (node1==0 || node2==0) {break;}
        else
            addEdge(G, node1, node2, weight);
            addEdge(G, node2, node1, weight);
    }
   
    printf("Enter the node to start the traversal from : \n");
    int n;
    scanf("%d", &n);

    dijkstra(G, n);
    print_dijkstra(G, n);
}
