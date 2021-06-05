#include <stdio.h>
#include <stdlib.h>

#define FILE_IN "in.txt"
#define FILE_OUT "out.txt"

typedef struct
{
    int x;
    int y;
    int px;
    int py;
    char flag;
} point;

int bfs(point **graph, int *s, int r, int c)
{
    int x[4] = {1, 0, -1, 0}, y[4] = {0, 1, 0, -1};
    typedef struct Queue
    {
        int x;
        int y;
        struct Queue *next;
    } queue;
    queue *h = malloc(sizeof(queue)), *t = h;
    graph[s[0]][s[1]].px = s[0];
    graph[s[0]][s[1]].py = s[1];
    h->x = s[0];
    h->y = s[1];
    h->next = NULL;
    int flag = 0;
    while (h)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (h->x + x[i] >= 0 && h->y + y[i] >= 0 && h->x + x[i] < r && h->y + y[i] < c)
            {
                if (graph[h->x + x[i]][h->y + y[i]].flag == 'E')
                {
                    graph[h->x + x[i]][h->y + y[i]].px = h->x;
                    graph[h->x + x[i]][h->y + y[i]].py = h->y;
                    flag = 1;
                    break;
                }
                else if (graph[h->x + x[i]][h->y + y[i]].flag == '0' && graph[h->x + x[i]][h->y + y[i]].px == -1)
                {
                    t->next = malloc(sizeof(queue));
                    t = t->next;
                    t->x = h->x + x[i];
                    t->y = h->y + y[i];
                    t->next = NULL;
                    graph[h->x + x[i]][h->y + y[i]].px = h->x;
                    graph[h->x + x[i]][h->y + y[i]].py = h->y;
                }
            }
        }
        queue *fr = h;
        h = h->next;
        free(fr);
        if (flag)
        {
            break;
        }
    }
    return flag;
}

int main()
{
    FILE *fi = fopen(FILE_IN, "r");
    int r = 0, c = 0, flag = 1;
    char ch;
    while ((ch = fgetc(fi)) != EOF)
    {
        if (ch != '\n')
        {
            if (flag)
            {
                ++r;
            }
        }
        else
        {
            flag = 0;
            ++c;
        }
    }

    point **maze = malloc(sizeof(point *) * r);
    for (int i = 0; i < r; ++i)
    {
        maze[i] = malloc(sizeof(point) * c);
    }

    rewind(fi);
    int s[2], e[2];
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            maze[i][j].x = i;
            maze[i][j].y = j;
            maze[i][j].px = maze[i][j].py = -1;
            maze[i][j].flag = fgetc(fi);
            if (maze[i][j].flag == 'S')
            {
                s[0] = i;
                s[1] = j;
            }
            else if (maze[i][j].flag == 'E')
            {
                e[0] = i;
                e[1] = j;
            }
        }
        fgetc(fi);
    }
    fclose(fi);

    FILE *fo = fopen(FILE_OUT, "w");
    if(bfs(maze, s, r, c)){
    int tempx = e[0], tempy = e[1];
    while (maze[tempx][tempy].px != maze[tempx][tempy].x || maze[tempx][tempy].py != maze[tempx][tempy].y)
    {
        int temp = tempx;
        tempx = maze[tempx][tempy].px;
        tempy = maze[temp][tempy].py;
        maze[tempx][tempy].flag = '*';
    }
    maze[s[0]][s[1]].flag = 'S';

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            fprintf(fo, "%c", maze[i][j].flag);
        }
        fprintf(fo, "\n");
    }}else{
        fprintf(fo, "没有路径");
    }
    fclose(fo);

    return 0;
}
