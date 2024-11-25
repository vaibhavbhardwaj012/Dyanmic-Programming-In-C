#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int parent, rank;
} Subset;

int compare(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void unionSets(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x), yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank) subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank) subsets[yroot].parent = xroot;
    else subsets[yroot].parent = xroot, subsets[xroot].rank++;
}

void kruskal(Edge edges[], int V, int E) {
    qsort(edges, E, sizeof(Edge), compare);
    Subset subsets[V];
    for (int v = 0; v < V; v++) subsets[v].parent = v, subsets[v].rank = 0;
    int e = 0, i = 0;
    while (e < V - 1) {
        Edge nextEdge = edges[i++];
        int x = find(subsets, nextEdge.src), y = find(subsets, nextEdge.dest);
        if (x != y) {
            printf("%d -- %d == %d\n", nextEdge.src, nextEdge.dest, nextEdge.weight);
            unionSets(subsets, x, y);
            e++;
        }
    }
}

int main() {
    Edge edges[] = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};
    int V = 4, E = sizeof(edges) / sizeof(edges[0]);
    kruskal(edges, V, E);
    return 0;
}

