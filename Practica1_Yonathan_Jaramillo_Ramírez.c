// Practica1_Shaman_Titan.c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100

// Represents an adjacency matrix for the graph
int graph[MAX_NODES][MAX_NODES];
int num_nodes;

// Function to generate a random delay between 1 and 1000
int generateRandomDelay() {
    return 1 + (rand() % 1000);
}

// Implementation of Dijkstra's algorithm for shortest paths from node 0
void dijkstra(int source, int dist[], int prev[]) {
    int visited[MAX_NODES];

    for (int i = 0; i < num_nodes; i++) {
        dist[i] = INT_MAX; // Initialize distances with a high value
        visited[i] = 0;   // Not yet visited
        prev[i] = -1;     // Previous node in path
    }

    dist[source] = 0;

    for (int count = 0; count < num_nodes - 1; count++) {
        int min = INT_MAX, min_index;

        for (int v = 0; v < num_nodes; v++) {
            if (visited[v] == 0 && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        }

        int u = min_index;
        visited[u] = 1;

        for (int v = 0; v < num_nodes; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                prev[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

// Function to print the shortest path from source to a given destination node
void printPath(int prev[], int j) {
    if (prev[j] == -1)
        return;

    printPath(prev, prev[j]);
    printf(" -> %d", j);
}

int main() {
    printf("Enter the number of nodes in the network: ");
    scanf("%d", &num_nodes);

    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            if (i != j) {
                // Assign a random delay between nodes
                graph[i][j] = generateRandomDelay();
                graph[j][i] = generateRandomDelay(); // Note: This assumes bidirectional communication
            } else {
                graph[i][j] = 0;
            }
        }
    }

    int distances[MAX_NODES];
    int prev[MAX_NODES];

    dijkstra(0, distances, prev);

    printf("Node\tDistance\tPath\n");
    for (int i = 1; i < num_nodes; i++) {
        printf("%d\t%d\t0", i, distances[i]);
        printPath(prev, i);
        printf("\n");
    }

    return 0;
}
