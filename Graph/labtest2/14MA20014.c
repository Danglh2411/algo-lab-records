//   Lab test 2 : Date : October 27, 2015
//   Submitted by : Himanshu Mishra (14MA20014)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define NIL 0
#define INFINITE INT_MAX

#define MAX_SIZE 1000	

#define YES 1
#define NO 0

struct listNode {
    int data;
    struct listNode *next;
};

struct listArray {
    struct listNode *next;
    int d;
    int p;
    int color;
};

struct Graph {
    int V;
    struct listArray *arr;
};

struct listNode* newNode(int data) {
    struct listNode* newListNode;
    newListNode = (struct listNode *)malloc(sizeof(struct listNode));
    newListNode->data = data;
    newListNode->next = NULL;

    return newListNode;
}

void addEdge(struct Graph* G, int node1, int node2) {
    struct listNode* temp;

    temp = newNode(node2);
    temp->next = G->arr[node1].next;
    G->arr[node1].next = temp;
}

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

int BFS_for_cycle(struct Graph *G, int s) {
	int cycle_detected;
	cycle_detected = NO;

    int i;
    for (i = 1; i <= G->V; ++i) {
        G->arr[i].color = WHITE;
        G->arr[i].d = INFINITE;
        G->arr[i].p = NIL;
    }

    G->arr[s].color = GRAY;
    G->arr[s].d = 0;

    struct Queue* Q;
    Q = (struct Queue *)malloc(sizeof(struct Queue));
    Q->length = MAX_SIZE - 1;
    Q->head = Q->tail = 0;

    ENQUEUE(Q, s);

    int u, v;
    while(Q->head!=Q->tail) {
        u = DEQUEUE(Q);
        struct listNode* iter;
        iter = G->arr[u].next;
        while(iter!=NULL) {
			if (G->arr[iter->data].d==G->arr[u].d || G->arr[iter->data].d==G->arr[u].d+1) {
				if (cycle_detected==NO) {
					cycle_detected = YES;
				}
			}
            else if (G->arr[iter->data].color==WHITE) {
                v = iter->data;
                G->arr[v].color = GRAY;
                G->arr[v].d = G->arr[u].d + 1;
                G->arr[v].p = u;
                ENQUEUE(Q, v);
            }
            iter = iter->next;
        }
        G->arr[u].color = BLACK;
    }

    return cycle_detected;
}

void BFS_for_connected(struct Graph *G, int s) {
	int i;    
	for (i = 1; i <= G->V; ++i) {
        G->arr[i].color = WHITE;
        G->arr[i].d = INFINITE;
        G->arr[i].p = NIL;
    }

    G->arr[s].color = GRAY;
    G->arr[s].d = 0;

    struct Queue* Q;
    Q = (struct Queue *)malloc(sizeof(struct Queue));
    Q->length = MAX_SIZE - 1;
    Q->head = Q->tail = 0;

    ENQUEUE(Q, s);

    int u, v;
    while(Q->head!=Q->tail) {
        u = DEQUEUE(Q);
        struct listNode* iter;
        iter = G->arr[u].next;
        while(iter!=NULL) {
            if (G->arr[iter->data].color==WHITE) {
                v = iter->data;
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

int BFS_for_odd(struct Graph *G, int s) {
    int cycle_detected;
    cycle_detected = NO;

	int i;
    for (i = 1; i <= G->V; ++i) {
        G->arr[i].color = WHITE;
        G->arr[i].d = INFINITE;
        G->arr[i].p = NIL;
    }

    G->arr[s].color = GRAY;
    G->arr[s].d = 0;

    struct Queue* Q;
    Q = (struct Queue *)malloc(sizeof(struct Queue));
    Q->length = MAX_SIZE - 1;
    Q->head = Q->tail = 0;

    ENQUEUE(Q, s);

    int u, v;
    while(Q->head!=Q->tail) {
        u = DEQUEUE(Q);
        struct listNode* iter;
        iter = G->arr[u].next;
        while(iter!=NULL) {
            if (G->arr[iter->data].d==G->arr[u].d) {
				if (cycle_detected==NO) {
					cycle_detected = YES;
				}
			}
            else if (G->arr[iter->data].color==WHITE) {
                v = iter->data;
                G->arr[v].color = GRAY;
                G->arr[v].d = G->arr[u].d + 1;
                G->arr[v].p = u;
                ENQUEUE(Q, v);
            }
            iter = iter->next;
        }
        G->arr[u].color = BLACK;
    }

return cycle_detected;
}

void reset(struct Graph *G) {
	int i;
	for (i=1; i<=G->V; i++) {
		G->arr[i].d = INFINITE;
		G->arr[i].p = NIL;
		G->arr[i].color = WHITE;
	}
}

int main()
{
    struct Graph* G;
    G = (struct Graph*)malloc(sizeof(struct Graph));

    printf("Enter the number of nodes : \n");
    scanf("%d", &G->V);

    G->arr = (struct listArray*)malloc((G->V+1)*sizeof(struct listArray));
    
    int i;
    for (i = 0; i<=G->V; i++) {
        G->arr[i].next = NULL;
    }

    int node1, node2;

    printf("Enter the pair of edges (0 0 to stop) :\n");
    while(true) {
        scanf("%d %d", &node1, &node2);
        if (node1==0 || node2==0) {break;}
        else {
            addEdge(G, node1, node2);
            addEdge(G, node2, node1);
        }
    }

    // Declarations
    int max_degree, m_d_node, degrees[G->V+1];
	struct listNode *iter;
    int cycle_detected;
	int components;
	int o_c_detected;

    int opt;

	printf("Enter your option :\n");
	printf("1. Find the maximum degree\n");
	printf("2. Test whether Graph is acyclic or not\n");
	printf("3. Find no. of connected components\n");
	printf("4. Test whether Graph has an odd cycle\n");
	printf("5. Exit\n");
	while(true) {
    scanf("%d", &opt);
	if (opt==5) {break;}
	else {
		switch(opt) {
		    case 1:
		        // Set all degrees to zero
		        for (i=0; i<=G->V; i++) {
		            degrees[i]=0;
		        }
		        // Calculate degrees
		        for (i=1; i<=G->V; i++) {
		            iter = G->arr[i].next;
		            while(iter!=NULL) {
		                ++degrees[i];
		                iter = iter->next;
		            }
		        }
		        max_degree = degrees[1];
		        m_d_node = 1;
		        for (i=2; i<=G->V; i++) {
		            if (degrees[i]>max_degree) {
		                max_degree = degrees[i];
		                m_d_node = i;
		            }
		        }
		        printf("The maximum degree is %d of node %d.\n", max_degree, m_d_node);
				reset(G);
		        break;
		    case 2:
		        cycle_detected=NO;
		        for (i=1; i<=G->V; i++) {
		            if (BFS_for_cycle(G, i)==YES) {
		                if (cycle_detected==NO) {
		                    cycle_detected=YES;
		                }
		            }
		        }
		        if (cycle_detected==YES) {
		            printf("The Graph is cyclic.\n");
		        }
		        else
		            printf("The Graph is acyclic\n");
				reset(G);
		        break;
		    case 3:
					components=0;
					for (i=1; i<=G->V; i++) {
						if (G->arr[i].color!=BLACK) {
							++components;
							BFS_for_connected(G, i);
						}
					}
					printf("The graph has %d connected components.\n", components);
				reset(G);
		        break;
		    case 4:
				o_c_detected=NO;			
				for(i=1; i<=G->V; i++) {
					if (o_c_detected==NO)
						o_c_detected = BFS_for_odd(G, i);
				}
				if (o_c_detected==NO)
					printf("Graph has no odd length cycle.\n");
				else
					printf("Graph has an odd length cycle.\n");
				reset(G);
		        break;
		}
	}
	}
}
