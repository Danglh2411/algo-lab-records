#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Stack implementation
struct stack {
    int data[100];
    int top=-1;
};

struct stack S;

void push(int data) {
	S.top = S.top + 1;
	S.data[S.top] = data;
}

int pop() {
	S.top = S.top - 1;
	return S.data[S.top + 1];
}

int top() {
    return S.data[S.top];
}

int is_empty() {
	if (S.top < 0) {return 1;}
	else return 0;
}

// Adjacency list implementation
typedef struct adjacencyList {
    int node;
    struct adjacencyList *ptr;
    struct adjacencyList *parent;
	int visited;
	int DFN;
} adjacencyList;

int main () {
    int n;  // Number of nodes in the graph
    printf("Enter the number of nodes : \n");
    scanf("%d", &n);    

    adjacencyList *adjl;  // Adjacency array of the nodes
    adjl = (adjacencyList *)malloc(n*sizeof(adjacencyList));  // Allocate the space for the base array

    // Feed the nodes
    for (int i = 0; i < n; ++i) {
        adjl[i].node = i;
    }
	printf("Graph with %d nodes, values starting from 0 has been created.\n\n", n);

    // Extend the elements of the base array of the adjacency list
    for (int i = 0; i < n; ++i) {
        printf("Enter the nodes connected to %d (Enter -1 to stop)\n", adjl[i].node);
        int nbr;
        adjacencyList *iter;
        iter = &adjl[i];
        for(;;) {
            scanf("%d", &nbr);
            if (nbr==-1) {break;}
            else
                iter->ptr = (adjacencyList *)malloc(sizeof(adjacencyList));
                iter->ptr->node = nbr;
                iter = iter->ptr;
                iter->ptr = NULL;
        }
    }  // Graph is now created as the Adjacency lists

    // Traversal
    int count;
    for (int i=0; i<n; i++) {
        adjl[i].DFN = 0;
        adjl[i].visited = 0;
        adjl[i].parent = NULL;
    }

    count = 1;
    push(0);
    adjl[0].visited = 1;
    adjl[0].DFN = count++;
    adjl[0].parent = &adjl[0];

    int x, y;
    adjacencyList *iter;
    while(!is_empty()) {
        x = top();
        iter = &adjl[x];
        while((iter->ptr)!=NULL) {
            iter = iter->ptr;
            if (iter->visited==0) {
                iter->DFN = count++;
                iter->visited = 1;
                iter->parent = &adjl[x];
                push(iter->node);
            }
        }
        pop();
    }


}
