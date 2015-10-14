/* Question 2 : Test whether a graph has a cycle or not using DFS

 * Submitted by : Himanshu Mishra
 * Roll : 14MA20014
 */

#define NIL 0

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NO 0
#define YES 1

// Stack implementation
struct stack {
    int data[100];
    int top;
};

void push(struct stack* S, int data) {
	S->top = S->top + 1;
	S->data[S->top] = data;
}

int pop(struct stack* S) {
	S->top = S->top - 1;
	return S->data[S->top + 1];
}

int top(struct stack* S) {
    return S->data[S->top];
}

int is_empty(struct stack* S) {
	if (S->top < 0) {return 1;}
	else return 0;
}

// Elements of the Adjacency List
struct listNode {
    int node;
    struct listNode *next;
};

// Elements of the array having pointers to the list
struct listArray {
    struct listNode *next;
    int visited;
    int DFN;
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
        printf("Node = %d, Parent = %d, DFN = %d, Visited = %d \n", i, G->arr[i].p, G->arr[i].DFN, G->arr[i].visited);
    }
}

// Depth First Traversal
void DFS(struct Graph* G, int v) {

	int cycle_detected;
	cycle_detected = NO;

    int temp_dfn;

    struct stack* S;
    S = (struct stack *)malloc(sizeof(struct stack));
    S->top = -1;

    // Traversal
    int count;
    for (int i = 1; i <= G->V; i++) {
        G->arr[i].DFN = 0;
        G->arr[i].visited = 0;
        G->arr[i].p = NIL;
    }

    count = 1;
    push(S, v);
    G->arr[v].visited = 1;
    G->arr[v].DFN = count++;
    G->arr[v].p = NIL;

    int x, y;
    struct listNode *iter;
    while(!is_empty(S)) {
        x = pop(S);
        iter = G->arr[x].next;
        while(iter!=NULL){
            if (G->arr[iter->node].visited==0) {
                G->arr[iter->node].DFN = count++;
                G->arr[iter->node].visited = 1;
                G->arr[iter->node].p = x;
                push(S, iter->node);
            }
            if (G->arr[iter->node].visited==1) {
                temp_dfn = G->arr[x].DFN;
                if (G->arr[iter->node].DFN == temp_dfn + 1) {}
                else if (G->arr[iter->node].DFN == temp_dfn) {}
                else {
    				if (cycle_detected==NO) {
    					printf("The Graph is cyclic.\n");
    					cycle_detected = YES;
    				}
                }

            }

            iter = iter->next;
        }
    }

    if (cycle_detected == NO)
        printf("The Graph is acyclic\n");
}

int main () {
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
            addEdge(G, node2, node2);
    }
    printf("Enter the node to start the traversal from : ");
    int n;
    scanf("%d", &n);
    DFS(G, n);
}
