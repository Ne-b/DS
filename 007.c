#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Link
{
    int id;
    int weight;
    struct Link *next;
} link;

typedef struct Point
{
    int temp;
    int in;
    int e;
    int l;
    link *link;
} point;

link *add_link(link *l, int id, int weight)
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
        l->next->id = id;
        l->next->weight = weight;
        l->next->next = NULL;
    }
    else
    {
        temp = malloc(sizeof(link));
        temp->id = id;
        temp->weight = weight;
        temp->next = NULL;
    }
    return temp;
}

void add(FILE *fi, point *graph)
{
    int a, b, c;
    fscanf(fi, "%d %d %d ", &a, &b, &c);
    graph[a].link = add_link(graph[a].link, b, c);
    graph[b].in++;
    graph[b].temp++;
}

void clear(point *graph)
{
    for (int i = 1; i <= graph[0].temp; ++i)
    {
        graph[i].temp = graph[i].in;
    }
}

int ve_vl(point *graph, int id)
{
    typedef struct Queue
    {
        int i;
        struct Queue *before;
        struct Queue *next;
    } queue;
    queue *h, *t, *p;
    h = malloc(sizeof(queue));
    p = t = h;
    h->i = id;
    h->before = h->next = NULL;

    while (p)
    {
        link *temp = graph[p->i].link;
        while (temp)
        {
            if (graph[temp->id].e < graph[p->i].e + temp->weight)
            {
                graph[temp->id].e = graph[p->i].e + temp->weight;
            }
            if (graph[temp->id].temp)
            {
                graph[temp->id].temp--;
                t->next = malloc(sizeof(queue));
                t->next->before = t;
                t = t->next;
                t->i = temp->id;
                t->next = NULL;
            }
            temp = temp->next;
        }
        p = p->next;
    }

    p = t;
    graph[p->i].l = graph[p->i].e;
    while (p)
    {
        link *temp = graph[p->i].link;
        if (graph[p->i].l < 0)
        {
            return 0;
        }
        if (temp)
        {
            graph[p->i].l = graph[temp->id].l - temp->weight;
            temp = temp->next;
        }
        while (temp)
        {
            if (graph[p->i].l > graph[temp->id].l - temp->weight)
            {
                graph[p->i].l = graph[temp->id].l - temp->weight;
            }
            temp = temp->next;
        }
        p = p->before;
        free(t);
        t = p;
    }
    clear(graph);
    return 1;
}

void key(FILE *fo, point *graph, int id)
{
    if (graph[id].temp == graph[id].in && graph[id].e == graph[id].l)
    {
        fprintf(fo, "%d ", id);
        graph[id].temp = -1;
        link *temp = graph[id].link;
        while (temp)
        {
            key(fo, graph, temp->id);
            temp = temp->next;
        }
    }
}

void print(FILE *fo, point *graph, int id)
{
    key(fo, graph, id);
    fprintf(fo, "\n");
    clear(graph);
}

int main()
{
    FILE *fi = fopen("D:\\Works\\C\\DS\\007\\007_i.txt", "r");
    int n;
    fscanf(fi, "%d ", &n);
    point *graph = malloc(sizeof(point) * (n + 1));
    memset(graph, 0, sizeof(point) * (n + 1));
    graph[0].temp = n;

    fscanf(fi, "%d ", &n);
    for (int i = 0; i < n; ++i)
    {
        add(fi, graph);
    }
    fclose(fi);

    if (ve_vl(graph, 1))
    {
        FILE *fo = fopen("D:\\Works\\C\\DS\\007\\007_o.txt", "w");
        print(fo, graph, 1);
        fclose(fo);
    }

    return 0;
}