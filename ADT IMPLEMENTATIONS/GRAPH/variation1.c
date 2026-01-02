#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXV 20

typedef struct node {
    int v;
    struct node *next;
} *AdjList;

typedef struct {
    int V;
    AdjList adj[MAXV];
} Graph;

void initGraph(Graph *g, int V) {
    g->V = V;
    for(int i = 0; i < V; i++) {
        g->adj[i] = NULL;
    }
}

void addEdge(Graph *g, int u, int v) {
    if(u < 0 || u >= g->V || v < 0 || v >= g->V) return;
    
    struct node *newNode = malloc(sizeof(struct node));
    newNode->v = v;
    newNode->next = g->adj[u];
    g->adj[u] = newNode;
    
    struct node *newNode2 = malloc(sizeof(struct node));
    newNode2->v = u;
    newNode2->next = g->adj[v];
    g->adj[v] = newNode2;
}

void removeEdge(Graph *g, int u, int v) {
    if(u < 0 || u >= g->V || v < 0 || v >= g->V) return;
    
    AdjList prev = NULL;
    for(AdjList curr = g->adj[u]; curr != NULL; prev = curr, curr = curr->next) {
        if(curr->v == v) {
            if(prev == NULL) {
                g->adj[u] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            break;
        }
    }
    
    prev = NULL;
    for(AdjList curr = g->adj[v]; curr != NULL; prev = curr, curr = curr->next) {
        if(curr->v == u) {
            if(prev == NULL) {
                g->adj[v] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            break;
        }
    }
}

int degree(Graph *g, int u) {
    if(u < 0 || u >= g->V) return 0;
    
    int count = 0;
    for(AdjList curr = g->adj[u]; curr != NULL; curr = curr->next) {
        count++;
    }
    return count;
}

void dfsUtil(Graph *g, int u, int *vis) {
    vis[u] = 1;
    printf("%d ", u);
    
    for(AdjList curr = g->adj[u]; curr != NULL; curr = curr->next) {
        if(vis[curr->v] == 0) {
            dfsUtil(g, curr->v, vis);
        }
    }
}

void dfs(Graph *g, int start) {
    int vis[MAXV] = {0};
    if(start < 0 || start >= g->V) return;
    dfsUtil(g, start, vis);
}

void bfs(Graph *g, int start) {
    int vis[MAXV] = {0};
    int q[MAXV], front = 0, rear = 0;
    
    if(start < 0 || start >= g->V) return;
    
    q[rear++] = start;
    vis[start] = 1;
    
    while(front < rear) {
        int u = q[front++];
        printf("%d ", u);
        
        for(AdjList curr = g->adj[u]; curr != NULL; curr = curr->next) {
            if(vis[curr->v] == 0) {
                q[rear++] = curr->v;
                vis[curr->v] = 1;
            }
        }
    }
}

int isConnected(Graph *g, int start) {
    int vis[MAXV] = {0};
    if(start < 0 || start >= g->V) return 0;
    
    dfsUtil(g, start, vis);
    
    for(int i = 0; i < g->V; i++) {
        if(vis[i] == 0) {
            return 0;
        }
    }
    return 1;
}

void printGraph(Graph *g) {
    printf("Adjacency lists:\n");
    for(int i = 0; i < g->V; i++) {
        printf("%d:", i);
        for(AdjList p = g->adj[i]; p != NULL; p = p->next) {
            printf(" %d", p->v);
        }
        printf("\n");
    }
}

int main(void) {
    Graph g;
    initGraph(&g, 7);
    
    addEdge(&g, 0, 1);
    addEdge(&g, 0, 2);
    addEdge(&g, 1, 3);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 4);
    addEdge(&g, 4, 5);
    addEdge(&g, 4, 6);
    
    printGraph(&g);
    
    printf("\nBFS from 0: ");
    bfs(&g, 0);
    printf("\nDFS from 0: ");
    dfs(&g, 0);
    printf("\nDegree of 3: %d\n", degree(&g, 3));
    printf("Connected from 0? %s\n", isConnected(&g, 0) ? "Yes" : "No");
    
    printf("\nRemoving edge (3,4)...\n");
    removeEdge(&g, 3, 4);
    printGraph(&g);
    printf("Degree of 3 now: %d\n", degree(&g, 3));
    
    return 0;
}

