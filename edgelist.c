#include "../graphutils.h" // header for functions to load and free adjacencyList

    void graphPrint (size_t graphNodeCount, AdjacencyListNode* adjacencyList) {

    // example of how to traverse the graph adjacency list
    for (size_t source = 0; source < (graphNodeCount); source++) {
        int dest2 = adjacencyList[source].graphNode;
        AdjacencyListNode* dest = adjacencyList[source].next;
        graphNode_t parent = source;

        // list iterator
        while (dest) {
            if (dest->graphNode != parent){
            //AdjacencyListNode* temp = dest;
            printf("%d ", dest2);
            printf("%ld\n", dest->graphNode);
            }
            dest = dest->next; // iterator moves to next

        }

    }
}

// A program to print the edge list of a graph given the adjacency matrix
int main ( int argc, char* argv[] ) {
    // FIRST, READ THE ADJACENCY MATRIX FILE

    AdjacencyListNode* adjacencyList = NULL;
    size_t numNodes = adjMatrixToList(argv[1], &adjacencyList);


    graphPrint(numNodes, adjacencyList);
    freeAdjList(numNodes, adjacencyList);

    return EXIT_SUCCESS;
}
