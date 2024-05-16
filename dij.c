#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Function to find the vertex with minimum distance value
int minDistance(int dist[], bool sptSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[], int V) {
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[][MAX_VERTICES], int src, int V) {
    int dist[MAX_VERTICES]; // The output array. dist[i] will hold the shortest distance from src to i
    bool sptSet[MAX_VERTICES]; // sptSet[i] will be true if vertex i is included in shortest
                    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet
        // processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet, V);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Print the constructed distance array
    printSolution(dist, V);
}

int main() {
    int V, E; // Number of vertices and edges
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    int graph[MAX_VERTICES][MAX_VERTICES]; // Adjacency matrix representation of the graph

    // Initialize graph with all zeros
    for (int i = 0; i < MAX_VERTICES; i++)
        for (int j = 0; j < MAX_VERTICES; j++)
            graph[i][j] = 0;

    // Input the edges and their weights
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        printf("Enter source, destination, and weight of edge %d: ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);
        graph[src][dest] = weight;
        graph[dest][src] = weight; // Assuming undirected graph
    }

    int src; // Source vertex for Dijkstra's algorithm
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, src, V);

    return 0;
}


/*
Enter the number of vertices and edges: 5 6
Enter source, destination, and weight of edge 1: 0 1 4
Enter source, destination, and weight of edge 2: 0 2 8
Enter source, destination, and weight of edge 3: 1 2 11
Enter source, destination, and weight of edge 4: 1 3 8
Enter source, destination, and weight of edge 5: 2 4 7
Enter source, destination, and weight of edge 6: 3 4 9
Enter the source vertex: 0
Vertex   Distance from Source
0         0
1         4
2         8
3         12
4         15

*/
