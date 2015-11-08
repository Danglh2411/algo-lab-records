/* Max-HEAP implementation */

#define MAX INT_MAX

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

void _swap(int *a, int *b) {
    int temp;
 
    temp = *a;
    *a = *b;
    *b = temp;
}

struct Heap {
    int arr[MAX];
    int size;
};

// Brind an elemnt up to maintain heap property
void AdjustUp(struct Heap* A, int i) {
    while(i>1) {
        if (A->arr[i/2]<A->arr[i]) {
            _swap(&A->arr[i/2], &A->arr[i]);
        }
        i = i/2;
    }
}

// Bring an element down to maintain heap property
void AdjustDown(struct Heap* A, int i) {
    int max;
    // If none of the children exist
    if (2*i > A->size) {
        // Nothing can be done
    }
    // If only the left child exist
    else if (2*i == A->size) {
        if (A->arr[2*i] > A->arr[i])
            _swap(&A->arr[i], &A->arr[2*i]);
        AdjustDown(A, 2*i);
    }
    // If both the children exist
    else {
        if (A->arr[2*i+1] > A->arr[2*i])
            max = 2*i+1;
        else
            max = 2*i;

        if (A->arr[max]>A->arr[i])
            _swap(&A->arr[max], &A->arr[i]);
        AdjustDown(A, max);
    }
}

// Construct a heap from a given array of elements
void heapify(struct Heap* A) {
    int i;
    for (i=A->size/2; i>0; i--) {
        AdjustDown(A, i);
    }
}

// Insert an element in the heap
void insert(struct Heap* A, int s) {
    ++A->size;
    A->arr[A->size] = s;
    AdjustUp(A, A->size);
}

// Delete the maximum element from the heap
void DeleteMax(struct Heap* A) {
    _swap(&A->arr[A->size], &A->arr[1]);
    --A->size;
    AdjustDown(A, 1);
}

// Delete and return the maximum element from the heap
int ExtractMax(struct Heap* A) {
    _swap(&A->arr[A->size], &A->arr[1]);
    --A->size;
    AdjustDown(A, 1);

    return A->arr[A->size + 1];
}

// Sort the heap array elements
void HeapSort(struct Heap* A) {
    int size = A->size;
    int sorted[size];
    int i;
    for (i=1; i<=size; i++) { 
        sorted[size - i] = ExtractMax(A);
    }

    for (i=0; i<size; i++) {
        printf("%d  ", sorted[i]);
    }
    printf("\n");
}

// Print out the heap array
void printHeap(struct Heap* A) {
    int i;
    for (i=1; i<=A->size; i++) {
        printf("%d  ", A->arr[i]);
    }
    printf("\n");
}

int main()
{
    struct Heap *A;
    A = (struct Heap *)malloc(sizeof(struct Heap));
    A->size=0;   // HEAP size

    printf("Enter max-heap elements (-1 to stop).\n");
    int temp; // To decide scanned integer
    while(true) {
        scanf("%d", &temp);
        if(temp==-1)
            break;
        else {
            A->size++;
            A->arr[A->size] = temp;
        }
    }

    // Call the heapify operation
    heapify(A);

    printHeap(A);
}
