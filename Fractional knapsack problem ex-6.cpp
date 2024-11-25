#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int weight, value;
    double ratio;
} Item;

int compare(const void *a, const void *b) {
    return ((Item *)b)->ratio > ((Item *)a)->ratio ? 1 : -1;
}

double fractionalKnapsack(int W, Item items[], int n) {
    qsort(items, n, sizeof(Item), compare);
    double totalValue = 0.0;
    for (int i = 0; i < n; i++) {
        if (W >= items[i].weight) {
            W -= items[i].weight;
            totalValue += items[i].value;
        } else {
            totalValue += items[i].ratio * W;
            break;
        }
    }
    return totalValue;
}

int main() {
    Item items[] = {{10, 60}, {20, 100}, {30, 120}};
    int W = 50, n = sizeof(items) / sizeof(items[0]);
    for (int i = 0; i < n; i++) items[i].ratio = (double)items[i].value / items[i].weight;
    printf("Maximum value: %.2f\n", fractionalKnapsack(W, items, n));
    return 0;
}

