#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    queue *h = malloc(sizeof(queue)), *t = h;
    graph[0][id] = 1;
    h->i = id;
    h->next = NULL;

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
    fprintf(fo, "\n");
    clear(graph);
}

int main()
{
    FILE *fi = fopen("D:\\Works\\C\\DS\\006\\2\\006_2_i.txt", "r");
    int n;
    fscanf(fi, "%d ", &n);
    int **graph = malloc(sizeof(int) * (n + 1));
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

    FILE *fo = fopen("D:\\Works\\C\\DS\\006\\2\\006_2_o.txt", "w");
    fprintf(fo, "DFS: ");
    dfs(fo, graph, 1);
    fprintf(fo, "BFS: ");
    bfs(fo, graph, 1);
    fclose(fo);

    return 0;
}