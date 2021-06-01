#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_IN stdin
#define FILE_OUT stdout

void add(FILE *fi, int **graph)
{
    int a, b;
    fscanf(fi, "%d %d ", &a, &b);
    graph[a][b] = graph[b][a] = 1;
}

void clear(int **graph)
{
    for (int i = 1; i <= graph[0][0]; ++i)
    {
        graph[0][i] = 0;
    }
}

void print_dfs(FILE *fo, int **graph, int id)
{
    if (!graph[0][id])
    {
        fprintf(fo, "%d ", id);
        graph[0][id] = 1;
        for (int i = 1; i <= graph[0][0]; ++i)
        {
            if (graph[id][i])
            {
                print_dfs(fo, graph, i);
            }
        }
    }
}

void dfs(FILE *fo, int **graph, int id)
{
    print_dfs(fo, graph, id);
    for (int i = 1; i <= graph[0][0]; ++i)
    {
        print_dfs(fo, graph, i);
    }
    fprintf(fo, "\n");
    clear(graph);
}

void print_bfs(FILE *fo, int **graph, int id)
{
    typedef struct Queue
    {
        int i;
        struct Queue *next;
    } queue;
    queue *h, *t;
    if (!graph[0][id])
    {
        h = malloc(sizeof(queue));
        t = h;
        graph[0][id] = 1;
        h->i = id;
        h->next = NULL;
    }
    else
    {
        h = NULL;
    }

    while (h)
    {
        fprintf(fo, "%d ", h->i);
        for (int i = 1; i <= graph[0][0]; ++i)
        {
            if (graph[h->i][i] && !graph[0][i])
            {
                graph[0][i] = 1;
                t->next = malloc(sizeof(queue));
                t = t->next;
                t->i = i;
                t->next = NULL;
            }
        }
        queue *fr = h;
        h = h->next;
        free(fr);
    }
}

void bfs(FILE *fo, int **graph, int id)
{
    print_bfs(fo, graph, id);
    for (int i = 1; i <= graph[0][0]; ++i)
    {

        print_bfs(fo, graph, i);
    }
    fprintf(fo, "\n");
    clear(graph);
}

int main()
{
    FILE *fi = fopen(FILE_IN, "r");
    int n;
    fscanf(fi, "%d ", &n);
    int **graph = malloc(sizeof(int *) * (n + 1));
    for (int i = 0; i <= n; ++i)
    {
        graph[i] = malloc(sizeof(int) * (n + 1));
        memset(graph[i], 0, sizeof(int) * (n + 1));
    }
    graph[0][0] = n;

    fscanf(fi, "%d ", &n);
    for (int i = 0; i < n; ++i)
    {
        add(fi, graph);
    }
    fclose(fi);

    FILE *fo = fopen(FILE_OUT, "w");
    fprintf(fo, "DFS: ");
    dfs(fo, graph, 1);
    fprintf(fo, "BFS: ");
    bfs(fo, graph, 1);
    fclose(fo);

    return 0;
}
