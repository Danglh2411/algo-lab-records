/* This file is a representation of an unweighted acyclic graph */
/* Using its adjacency list. */

/* __all__ = ['addEdge', 'printGraph'] */
/* __author__ = "Himanshu Mishra" */

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

// Elements of the Adjacency List
struct listNode {
    int node;
    struct listNode *next;
};

// Elements of the array having pointers to the list
struct listArray {
    struct listNode *next;
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
void addEdge(struct Graph* G, int node1, int node2) {
    struct listNode* newNode = newListNode(node2);
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
            printf("-> %d ", iter->node);
            iter = iter->next;
        }
        printf("\n");
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
    for (int i=1; i<=V; i++) {
        G->arr[i].next = NULL;
    }

    printf("Enter pair of nodes to add Edge :\n");
    printf("(Enter (0, 0) to terminate)\n");
    int node1, node2;
    while(true) {
        scanf("%d %d", &node1, &node2);
        if (node1==0 || node2==0) {break;}
        else
            addEdge(G, node1, node2);
    }

    printGraph(G);

}
