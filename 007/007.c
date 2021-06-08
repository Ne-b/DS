#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_IN "in.txt"
#define FILE_OUT "out.txt"

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

void print(FILE *fo, point *graph, int *h, int p)
{

    while (p >= 0)
    {
        int tempid = h[p], flag = 1;

        if (!graph[tempid].link)
        {
            for (int i = 0; i <= p; ++i)
            {
                fprintf(fo, "%d ", h[i]);
            }
            fprintf(fo, "\n");
            --p;
            graph[tempid].temp = -1;
            continue;
        }

        link *templk = graph[tempid].link;
        while (templk)
        {
            if (graph[templk->id].temp == graph[templk->id].in && graph[templk->id].e == graph[templk->id].l)
            {
                flag = 0;
                break;
            }
            templk = templk->next;
        }
        if (flag)
        {
            --p;
            graph[tempid].temp = -1;
            continue;
        }

        templk = graph[tempid].link;
        while (templk)
        {
            if (graph[templk->id].temp == graph[templk->id].in && graph[templk->id].e == graph[templk->id].l)
            {
                h[++p] = templk->id;
                print(fo, graph, h, p);
            }
            templk = templk->next;
        }
    }
}

int main()
{
    FILE *fi = fopen(FILE_IN, "r");
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
        FILE *fo = fopen(FILE_OUT, "w");
        int *h = malloc(sizeof(int) * graph[0].temp);
        memset(h, 0, sizeof(int) * graph[0].temp);
        int p = 0;
        h[p] = 1;
        print(fo, graph, h, p);
        clear(graph);
        fclose(fo);
    }

    return 0;
}
