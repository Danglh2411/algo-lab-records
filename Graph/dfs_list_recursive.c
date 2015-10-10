/* This file is an implementation of the Depth first Search */
/* Of a Graph using Queue. */

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define NIL 0

#define MAX_SIZE 100

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

int time;  // Global variable

// Elements of the Adjacency List
struct listNode {
    int node;
    struct listNode *next;
};

// Elements of the array having pointers to the list
struct listArray {
    struct listNode *next;
    int color;
    int d;  // Distance
    int p;  // Parent
    int f;  // Finishing time
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
    printf("\n");
    for (int i = 1; i <= G->V; ++i) {
        printf("Node = %d, Parent = %d, Distance = %d,", i, G->arr[i].p, G->arr[i].d);
        switch (G->arr[i].color) {
            case 0:
                printf(" Color = WHITE\n");
                break;
            case 1:
                printf(" Color = GRAY\n");
                break;
            case 2:
                printf(" Color = BLACK\n");
                break;
        }

    }
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

void DFS_VISIT(struct Graph* G, int u) {
    struct listNode* iter;    
    iter = G->arr[u].next;

    G->arr[u].color = GRAY;
    time = time + 1;
    G->arr[u].d = time;

    while(iter!=NULL) {
        if (G->arr[iter->node].color==WHITE) {
            G->arr[iter->node].p = u;
            DFS_VISIT(G, iter->node);
        }
        iter = iter->next;
    }
    
    G->arr[u].color = BLACK;
    time = time + 1;
    G->arr[u].f = time;
}

void DFS(struct Graph* G) {
    for (int i = 1; i <= G->V; ++i) {
        G->arr[i].color = WHITE;
        G->arr[i].p = NIL;
    }

    time = 0;

    for (int i = 1; i <= G->V; ++i) {
        if (G->arr[i].color==WHITE) {
            DFS_VISIT(G, i);
        }
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

    printf("Enter pair of nodes to add Edge :\n");
    printf("(Enter (0, 0) to terminate)\n");
    int node1, node2;
    while(true) {
        scanf("%d %d", &node1, &node2);
        if (node1==0 || node2==0) {break;}
        else
            addEdge(G, node1, node2);
            addEdge(G, node2, node1);
    }

    DFS(G);
    printGraph(G);


}
