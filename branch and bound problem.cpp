#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int level, profit, weight;
    float bound;
} Node;

typedef struct {
    Node *data;
    int front, rear, capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->capacity = capacity;
    q->front = q->rear = -1;
    q->data = (Node *)malloc(capacity * sizeof(Node));
    return q;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, Node item) {
    if (q->rear == q->capacity - 1) return;
    if (q->front == -1) q->front = 0;
    q->data[++q->rear] = item;
}

Node dequeue(Queue *q) {
    Node item = q->data[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return item;
}

float bound(Node u, int n, int W, int val[], int wt[]) {
    if (u.weight >= W) return 0;
    float profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;

    while (j < n && totweight + wt[j] <= W) {
        totweight += wt[j];
        profit_bound += val[j];
        j++;
    }

    if (j < n)
        profit_bound += (W - totweight) * ((float)val[j] / wt[j]);

    return profit_bound;
}

int knapsackBranchAndBound(int W, int wt[], int val[], int n) {
    Queue *q = createQueue(1000);
    Node u, v;

    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = bound(u, n, W, val, wt);

    enqueue(q, u);

    int maxProfit = 0;
    while (!isEmpty(q)) {
        u = dequeue(q);

        if (u.level == n - 1) continue;

        v.level = u.level + 1;

        v.weight = u.weight + wt[v.level];
        v.profit = u.profit + val[v.level];

        if (v.weight <= W && v.profit > maxProfit)
            maxProfit = v.profit;

        v.bound = bound(v, n, W, val, wt);

        if (v.bound > maxProfit)
            enqueue(q, v);

        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, W, val, wt);

        if (v.bound > maxProfit)
            enqueue(q, v);
    }

    free(q->data);
    free(q);

    return maxProfit;
}

int main() {
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);
    printf("Branch and Bound: Maximum value: %d\n", knapsackBranchAndBound(W, wt, val, n));
    return 0;
}

