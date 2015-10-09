// Implementation of Queue using Doubly Linked List

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

// A Queue data structure
struct Queue {
    int data;
    struct Queue *next;
    struct Queue *back;
};

struct QueueHandlers {
    struct Queue *first;
    struct Queue *last;
};

// Function to remove an element from Queue and return the node
int DEQUEUE(struct QueueHandlers *QH) {
    int to_return;
    if (QH->first==NULL && QH->last==NULL) {printf("Sorry the Queue is empty!\n");}
    else {
        to_return = QH->first->data;
        if (QH->first == QH->last) {
            QH->first = NULL;
            QH->last = NULL;
        }
        else {
            QH->first = QH->first->back;
            QH->first->next = NULL;

        return to_return;
        }
    }
}

// Function to add an element to the Queue
void ENQUEUE(struct QueueHandlers *QH, int data) {
    if (QH->last!=NULL) {
        QH->last->back = (struct Queue *)malloc(sizeof(struct Queue));
        QH->last->back->next = QH->last;
        QH->last = QH->last->back;
        QH->last->back = NULL;
        QH->last->data = data;
    }
    else if(QH->last==NULL) {
        struct Queue* temp;
        temp = (struct Queue *)malloc(sizeof(struct Queue));
        temp->back = NULL;
        temp->next = NULL;
        temp->data = data;
        QH->last = temp;
        QH->first = temp;
    }


}

void printQueue(struct QueueHandlers *QH) {
    struct Queue* iter = QH->first;
    printf("%d ", iter->data);
    while(true) {
        if (iter->back==NULL) {break;}
        else
            iter = iter->back;
            printf("-> %d ", iter->data);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{

    // Create empty Queue
    struct QueueHandlers* QH;
    QH = (struct QueueHandlers*)malloc(sizeof(struct QueueHandlers));
    QH->last = NULL;
    QH->first = NULL;

    ENQUEUE(QH, 1);
    ENQUEUE(QH, 2);
    DEQUEUE(QH);
    ENQUEUE(QH, 5);
    ENQUEUE(QH, 6);
    DEQUEUE(QH);
    ENQUEUE(QH, 7);

    printQueue(QH);
   
}
