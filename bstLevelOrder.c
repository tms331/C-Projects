#include <stdlib.h>
#include <stdio.h>

// BINARY SEARCH TREE
typedef struct BSTNode BSTNode;
struct BSTNode {
    int key;
    struct BSTNode* l_child; // nodes with smaller key will be in left subtree
    struct BSTNode* r_child; // nodes with larger key will be in right subtree
};

// Add new data to the BST using recursion
struct BSTNode* insert ( struct BSTNode* root, int key ) {

    // If the BSTNode doesn't yet exist
    if (root == NULL) {
        root = malloc(sizeof(BSTNode));
        root->key = key;
        root->l_child = NULL;
        root->r_child = NULL;

    }

    // If the BSTNode already exists, then insert key in correct subtree
    if ( key < root->key ) {
        root->l_child = insert( root->l_child, key );

    } else if ( key == root->key ) { // duplicates are ignored
        
    } else { // key > root->key
        root->r_child = insert( root->r_child, key );
    }

    return root;
}

// Delete the BST using recursion
void delete_bst ( BSTNode* root ) {
    if ( root->r_child != NULL ) {
        delete_bst (root->r_child);
    }

    if ( root->l_child != NULL ) {
        delete_bst (root->l_child);
    }

    free (root);
}


// queue needed for level order traversal
typedef struct QueueNode QueueNode;
struct QueueNode {
    BSTNode* data;
    struct QueueNode* next; // pointer to next node in linked list
};

struct Queue {
    struct QueueNode* front; // front (head) of the queue
    struct QueueNode* back; // back (tail) of the queue
};
typedef struct Queue Queue;

// Append a new QueueNode to the back of the Queue
void enqueue ( Queue* queue, BSTNode* data ) {

    //printf("key: %d\n", data->key);

    QueueNode* queueNode = malloc(sizeof(QueueNode));
    queueNode -> data = data;
    queueNode -> next = NULL; // At back of the queue, there is no next node.

    if (queue->back == NULL) { // If the Queue is currently empty
        queue->front = queueNode;
        queue->back = queueNode;

    } else {
        queue->back->next = queueNode;
        queue->back = queueNode;
    }

    return;
}

void level_first (Queue* queue) {
    if(queue->front != NULL) // printing of queue will only continue until the queue empty
    {
        QueueNode* temp;
        printf(" %d ", queue->front->data->key); // printing data at front

        temp = queue->front; // pointer "dance" to be able to properly free printed item
        queue->front = temp->next; // move up front to the next item to be printed
        free(temp); // free the already printed item, no memory leak

        level_first(queue); // recursive call to continue printing the queue until empty
    }
}

int main ( int argc, char* argv[] ) {

    BSTNode* root = NULL;
    int key;

    // READ INPUT FILE TO CREATE BINARY SEARCH TREE
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    while ( fscanf(fp, "%d", &key) != EOF ) {
        root = insert (root, key);
    }
    fclose(fp);

    // USE A QUEUE TO PERFORM LEVEL ORDER TRAVERSAL
    Queue queue = { .front = NULL, .back = NULL };
    QueueNode* currQueueNode;

    if(root != NULL){
        enqueue(&queue, root);
    }

    currQueueNode = queue.front;

    do {

        if(currQueueNode->data->l_child != NULL){
            enqueue(&queue, currQueueNode->data->l_child);
        }

        if(currQueueNode->data->r_child != NULL){
            enqueue(&queue, currQueueNode->data->r_child);
        }            

        currQueueNode = currQueueNode->next;

    } while ( currQueueNode != NULL );


    level_first(&queue);
    delete_bst(root);
    return EXIT_SUCCESS;
}