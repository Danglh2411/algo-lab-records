// Problem in deleting root node

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int data;
    struct node *parent;
    struct node *left;
    struct node *right;
};

struct bst {
    int size;
    struct node *root;
};

// Insert an element in a binary search tree
void insert(struct bst *T, int data) {
    struct node* iter;
    // If the tree isn't initialized
    if (T->root==NULL) {
        T->root = (struct node *)malloc(sizeof(struct node));
        T->root->parent = NULL;
        T->root->left = NULL;
        T->root->right = NULL;
        T->root->data = data;
    }
    else {
        iter = T->root;
        while(true) {
            if (data<iter->data) {
                if (iter->left==NULL)
                    break;
                else
                    iter = iter->left;
            }
            else {
                if (iter->right==NULL)
                    break;
                else
                    iter = iter->right;
            }
        }
        if (data<iter->data) {
            iter->left = (struct node *)malloc(sizeof(struct node));
            iter->left->data = data;
            iter->left->parent = iter;
            iter->left->left = NULL;
            iter->left->right = NULL;
        }
        else {
            iter->right = (struct node *)malloc(sizeof(struct node));
            iter->right->data = data;
            iter->right->parent = iter;
            iter->right->left = NULL;
            iter->right->right = NULL;
        }
    }
}

// Search a number and return a pointer to it
struct node* search(struct bst *T, int data) {
    struct node* iter;

    iter = T->root;
    while(iter!=NULL) {
        if(iter->data==data) {
            return iter;
        }
        else {
            if(data<iter->data)
                iter = iter->left;
            else
                iter = iter->right;
        }
    }

    return iter;
}

// Find the minimum node of a tree
struct node* min(struct node *root) {
    struct node* iter;
    iter = root;
    while(iter->left!=NULL) {
        iter = iter->left;
    }

    return iter;
}

// Find the maximum node of a tree
struct node* max(struct node* root) {
    struct node* iter;
    iter = root;
    while(iter->right!=NULL) {
        iter = iter->right;
    }

    return iter;
}

// Return the predecessor of a node in a tree
struct node* predecessor(struct node *root) {
    struct node* iter;
    
    iter = root->left;
    if (iter==NULL) {
        return iter;
    }
    else {
        while(iter->right) {
            iter = iter->right;
        }   
    }

    return iter;
}

// Return the successor of a node in a tree
struct node* successor(struct node *root) {
    struct node* iter;

    iter = root->right;
    if (iter==NULL) {
        return iter;
    }
    else {
        while(iter->left!=NULL) {
            iter = iter->left;
        }
    }

    return iter;
}

// Delete a node from the tree
void delete_node(struct bst *T, int data) {
    struct node* iter;
    iter = search(T, data);

    // No such node
    if (iter==NULL) {
        printf("No such node to delete.");
    }
    else {
        // Leaf node
        if (iter->right==NULL && iter->left==NULL) {
            if (iter->parent!=NULL) {
                if (iter->parent->data<iter->data)
                    iter->parent->right = NULL;
                else
                    iter->parent->left = NULL;
            }
        }
        // Node with right child
        else if(iter->left==NULL && iter->right!=NULL) {
            if (iter->parent!=NULL) {
                iter->right->parent = iter->parent;
                if (iter->parent->data<iter->data)
                    iter->parent->right = iter->right;
                else
                    iter->parent->left = iter->right;
            }
        }
        // Node with left child
        else if(iter->left!=NULL && iter->right==NULL) {
            if (iter->parent!=NULL) {
                iter->left->parent = iter->parent;
                if (iter->parent->data<iter->data)
                    iter->parent->right = iter->left;
                else
                    iter->parent->left = iter->left;
            }
        }
        // Node with both children
        else if(iter->left!=NULL & iter->right!=NULL) {
            struct node *next;
            int next_data;

            next = predecessor(iter); // Find the predecessor
            if (next==NULL) {
                next = successor(iter);
            }
            if (next==NULL) {
                printf("Deleting the root node.");
                free(T->root);
                return;
            }
            next_data = next->data;
            delete_node(T, next->data); // Delete the predecessor node
            iter->data = next_data; // Put that in the iter's position
        }
    }
}

// Pre-order traversal
void preorder(struct node* root) {
    if (root==NULL)
        return;

    printf(" %d ", root->data);
    preorder(root->left);
    preorder(root->right);

}

// In-order traversal
void inorder(struct node* root) {
    if (root==NULL) 
        return;
    
    inorder(root->left);
    printf(" %d ", root->data);
    inorder(root->right);
}

// Post-order traversal
void postorder(struct node* root) {
    if (root==NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    printf(" %d ", root->data);
}

int main()
{
    struct bst *T;
    T = (struct bst *)malloc(sizeof(struct bst));
    T->size = 0;
    printf("Start entering the numbers for the BST (-1 to break):\n");
    int temp; // For deciding the scanned number
    while(true) {
        scanf("%d", &temp);
        if(temp==-1)
            break;
        else {
            ++T->size;
            insert(T, temp);
        }
    }

    int choice, to_delete, to_insert, no_to_search;
    while(true) {
        printf("1. To find a number in the binary search tree.\n");
        printf("2. To insert a number in the binary search tree.\n");
        printf("3. To delete a number in the binary search tree.\n");
        printf("4. Pre-order traversal.\n");
        printf("5. In-order traversal.\n");
        printf("6. Post-order traversal.\n");
        printf("0. To Quit program.\n");
        scanf("%d", &choice);
        if (choice==0)
            break;
        switch(choice) {
            case 1:
                printf("Enter the number to seach :\n");
                scanf("%d", &no_to_search);
                struct node* search_t;
                search_t = search(T, no_to_search);
                if (search_t!=NULL)
                    printf("Yes, %d is present in the tree.\n", no_to_search);
                else
                    printf("Couldn't find the number %d in the tree.\n", no_to_search);
                break;
            case 2:
                printf("Enter the number to insert :\n");
                scanf("%d", &to_insert);
                insert(T, to_insert);
                break;
            case 3:
                printf("Enter the number to delete :\n");
                scanf("%d", &to_delete);
                delete_node(T, to_delete);
                choice = -1;
            case 4:
                preorder(T->root);
                printf("\n");
                choice = -1;
                break;
            case 5:
                inorder(T->root);
                printf("\n");
                choice = -1;
                break;
            case 6:
                postorder(T->root);
                printf("\n");
                choice = -1;
                break;
        }
    }
}
