#include <stdio.h>
#include <limits.h>

typedef struct {
    int src, dest, weight;
} Edge;

void bellmanFord(Edge edges[], int V, int E, int src) {
    int dist[V];
    for (int i = 0; i < V; i++) dist[i] = INT_MAX;
    dist[src] = 0;
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src, v = edges[j].dest, w = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) dist[v] = dist[u] + w;
        }
    }
    for (int i = 0; i < V; i++) printf("%d ", dist[i]);
}

int main() {
    Edge edges[] = {{0, 1, 10}, {1, 2, 5}, {2, 3, 20}, {2, 4, 1}, {3, 4, 2}};
    int V = 5, E = sizeof(edges) / sizeof(edges[0]);
    bellmanFord(edges, V, E, 0);
    return 0;
}

