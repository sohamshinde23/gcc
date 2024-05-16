#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define MAX_EDGES 100

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Function to print the final distances
void printDistances(int dist[], int V) {
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("%d \t\t INFINITY\n", i);
        else
            printf("%d \t\t %d\n", i, dist[i]);
    }
}

// Bellman-Ford algorithm function
void bellmanFord(struct Edge edges[], int V, int E, int src) {
    int dist[MAX_VERTICES];

    // Initialize distances from source to all other vertices as INFINITE
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle, cannot find shortest paths\n");
            return;
        }
    }

    // Print the final distances
    printDistances(dist, V);
}

int main() {
    int V, E; // Number of vertices and edges
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    struct Edge edges[MAX_EDGES]; // Array to store edges of the graph

    // Input the edges and their weights
    for (int i = 0; i < E; i++) {
        printf("Enter source, destination, and weight of edge %d: ", i + 1);
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    int src; // Source vertex for Bellman-Ford algorithm
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    bellmanFord(edges, V, E, src);

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
4         19

*/
