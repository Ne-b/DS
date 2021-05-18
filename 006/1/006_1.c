#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Link
{
    int node_id;
    struct Link *next;
} link;

typedef struct Node
{
    int flag;
    link *link;
} node;

link *add_link(link *l, int id)
{
    link *temp;
    if (l)
    {
        temp = l;
        while (l->next)
        {
            l = l->next;
        }
        l->next = malloc(sizeof(link));
        l->next->node_id = id;
        l->next->next = NULL;
    }
    else
    {
        temp = malloc(sizeof(link));
        temp->node_id = id;
        temp->next = NULL;
    }
    return temp;
}

void add(FILE *fi, node *graph)
{
    int a, b;
    fscanf(fi, "%d %d ", &a, &b);
    graph[a].link = add_link(graph[a].link, b);
    graph[b].link = add_link(graph[b].link, a);
}

void clear(node *graph)
{
    for (int i = 1; i <= graph[0].flag; ++i)
    {
        graph[i].flag = 0;
    }
}

void print_dfs(FILE *fo, node *graph, int id)
{
    if (!graph[id].flag)
    {
        fprintf(fo, "%d ", id);
        graph[id].flag = 1;
        link *temp = graph[id].link;
        while (temp)
        {
            print_dfs(fo, graph, temp->node_id);
            temp = temp->next;
        }
    }
}

void dfs(FILE *fo, node *graph, int id)
{
    print_dfs(fo, graph, id);
    fprintf(fo, "\n");
    clear(graph);
}

void print_bfs(FILE *fo, node *graph, int id)
{
    typedef struct Queue
    {
        int i;
        struct Queue *next;
    } queue;
    queue *h = malloc(sizeof(queue)), *t = h;
    graph[id].flag = 1;
    h->i = id;
    h->next = NULL;

    while (h)
    {
        fprintf(fo, "%d ", h->i);
        link *temp = graph[h->i].link;
        while (temp)
        {
            if (!graph[temp->node_id].flag)
            {
                graph[temp->node_id].flag = 1;
                t->next = malloc(sizeof(queue));
                t = t->next;
                t->i = temp->node_id;
                t->next = NULL;
            }
            temp = temp->next;
        }
        queue *fr = h;
        h = h->next;
        free(fr);
    }
}

void bfs(FILE *fo, node *graph, int id)
{
    print_bfs(fo, graph, id);
    fprintf(fo, "\n");
    clear(graph);
}

int main()
{
    FILE *fi = fopen("D:\\Works\\C\\DS\\006\\1\\006_1_i.txt", "r");
    int n;
    fscanf(fi, "%d ", &n);
    node *graph = malloc(sizeof(node) * (n + 1));
    memset(graph, 0, sizeof(node) * (n + 1));
    graph[0].flag = n;

    fscanf(fi, "%d ", &n);
    for (int i = 0; i < n; ++i)
    {
        add(fi, graph);
    }
    fclose(fi);

    FILE *fo = fopen("D:\\Works\\C\\DS\\006\\1\\006_1_o.txt", "w");
    fprintf(fo, "DFS: ");
    dfs(fo, graph, 1);
    fprintf(fo, "BFS: ");
    bfs(fo, graph, 1);
    fclose(fo);

    return 0;
}
