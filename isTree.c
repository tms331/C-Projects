#include "../graphutils.h" // header for functions to load and free adjacencyList
// A program to determine whether an undirected graph is a tree
// A recursive function that returns true if no cycles found

bool isTreeDFS (
    size_t graphNodeCount,
    AdjacencyListNode* adjacencyList,
    bool* visited,
    graphNode_t parent,
    graphNode_t current
) {

    if(visited[current] == true){
        return false;
    }

    visited[current] = true;
    AdjacencyListNode* neighbor = adjacencyList[current].next;

    while (neighbor) {
        if (neighbor->graphNode != parent) {
            if(isTreeDFS(graphNodeCount, adjacencyList, visited, current, neighbor->graphNode) == false){
                return false;
            }
        }
        neighbor = neighbor->next;
    }


    // All DFS searches from current node found no cycles, so graph is a tree from this node
    return true;
}

int main ( int argc, char* argv[] ) {
    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList = NULL;
    graphNode_t parent = 0;
    graphNode_t current = 0;

    size_t numNodes = adjMatrixToList(argv[1], &adjacencyList);

    // Array of boolean variables indicating whether graph node has been visited
    bool* visited = calloc (numNodes, sizeof(bool));

    bool isTree = isTreeDFS(numNodes, adjacencyList, visited, parent, current);
    printf(isTree ? "yes\n" : "no\n");


    freeAdjList(numNodes, adjacencyList);
    free(visited);
    return EXIT_SUCCESS;
}