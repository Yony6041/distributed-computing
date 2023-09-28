#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100

// Representa una matriz de adyacencia para el grafo
int graph[MAX_NODES][MAX_NODES];
int num_nodes;

// Función para generar un retraso aleatorio entre 1 y 1000
int generateRandomDelay() {
    return 1 + (rand() % 1000);
}

// Implementación del algoritmo de Dijkstra para las rutas más cortas desde el nodo 0
void dijkstra(int source, int dist[], int prev[]) {
    int visited[MAX_NODES];

    for (int i = 0; i < num_nodes; i++) {
        dist[i] = INT_MAX; // Inicializar distancias con un valor alto
        visited[i] = 0;   // Aún no visitado
        prev[i] = -1;     // Nodo anterior en la ruta
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

// Función para imprimir la ruta más corta desde la fuente a un nodo destino dado
void printPath(int prev[], int j) {
    if (prev[j] == -1)
        return;

    printPath(prev, prev[j]);
    printf(" -> %d", j);
}

int main() {
    printf("Ingrese el número de nodos en la red: ");
    scanf("%d", &num_nodes);

    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            if (i != j) {
                // Asignar un retraso aleatorio entre nodos
                graph[i][j] = generateRandomDelay();
                graph[j][i] = generateRandomDelay(); // Nota: Esto asume comunicación bidireccional
            } else {
                graph[i][j] = 0;
            }
        }
    }

    int distances[MAX_NODES];
    int prev[MAX_NODES];

    dijkstra(0, distances, prev);

    printf("Nodo\tDistancia\tRuta\n");
    for (int i = 1; i < num_nodes; i++) {
        printf("%d\t%d\t0", i, distances[i]);
        printPath(prev, i);
        printf("\n");
    }

    return 0;
}
