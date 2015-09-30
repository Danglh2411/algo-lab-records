/* This file takes an unweighted Graph as input and stores */
/* the nodes as the elements of Adjacency Lists. Breadth-first */
/* search and Depth-first search are implemented using it */

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

// struct used for the data structure elements of the Adjacency List
typedef struct adjacencyList {
    int node;
    struct adjacencyList *ptr;
} adjacencyList;

// Return the index of an element in an array
int _index(adjacencyList A[], int node) {
    int i;
    i = 0;
    for (;;) {
        if (A[i].node==node) {return i;}
        else
            i++;
    }
}

int main(int argc, char const *argv[])
{
    int n;  // Number of nodes in the graph
    printf("Enter the number of nodes : \n");
    scanf("%d", &n);

    adjacencyList *adjl;  // Adjacency array of the nodes
    adjl = (adjacencyList *)malloc(n*sizeof(adjacencyList));  // Allocate the space for the base array

    // Feed the nodes
    printf("Enter the values of all the %d nodes : \n", n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &adjl[i].node);
    }

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


// To check if two nodes share a common edge
/*    

    int node1, node2;
    printf("Now we are going to check whether two nodes are connected or not.\n");
    printf("\n Enter two nodes : \n");
    scanf("%d %d", &node1, &node2);

    adjacencyList *iter;
    while(true) {
        iter = &adjl[_index(adjl, node1)];
        if (iter->ptr==NULL) {printf("No, node 1 is a loner.\n");}
        else 
            iter = iter->ptr;
            for(;;) {
                if (iter->node == node2) {printf("Yes\n"); break;}
                else if (iter->ptr==NULL) {printf("No\n"); break;}
                else
                    iter = iter->ptr;
                }
        }

    }
*/    

}
