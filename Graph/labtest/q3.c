/* Question 3 : Test whether a Graph has an odd length cycle or not using BFS 

 * Submitted by : Himanshu Mishra
 * Roll : 14MA20014
 */

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define NIL 0
#define INFINITE -1

#define MAX_SIZE 100

#define NO 0
#define YES 1

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
    int color;
    int d;
    int p;
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
        printf("Node = %d, Parent = %d, Distance = %d, Color = %d \n", i, G->arr[i].p, G->arr[i].d, G->arr[i].color);
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

void BFS(struct Graph *G, int s) {
    int cycle_detected;
    cycle_detected = NO;

    // Set configurations of all the nodes
    for (int i = 1; i <= G->V; ++i) {
        G->arr[i].color = WHITE;
        G->arr[i].d = INFINITE;
        G->arr[i].p = NIL;
    }

    // For the root
    G->arr[s].color = GRAY;
    G->arr[s].d = 0;

    // Create empty Queue
    struct Queue* Q;
    Q = (struct Queue *)malloc(sizeof(struct Queue));
    Q->length = MAX_SIZE - 1;
    Q->head = Q->tail = 0;

    // Start the traversal
    ENQUEUE(Q, s);

    int u, v;
    while(Q->head!=Q->tail) {
        u = DEQUEUE(Q);
        struct listNode* iter;
        iter = G->arr[u].next;
        while(iter!=NULL) {
            if (G->arr[iter->node].d==G->arr[u].d)  {  // Key Point
				if (cycle_detected==NO) {
					printf("The Graph has an odd length cycle.\n");
					cycle_detected = YES;
				}
			}
            else if (G->arr[iter->node].color==WHITE) {
                v = iter->node;
                G->arr[v].color = GRAY;
                G->arr[v].d = G->arr[u].d + 1;
                G->arr[v].p = u;
                ENQUEUE(Q, v);
            }
            iter = iter->next;
        }
        G->arr[u].color = BLACK;
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
    
    printf("Enter the node to start the traversal from : ");
    int n;
    scanf("%d", &n);
    BFS(G, n);
   

}

