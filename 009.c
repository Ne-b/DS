#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 1021

typedef struct Link
{
    char *name;
    char *num;
    struct Link *next;
} link;

link list[N] = {0};

int main()
{
    char temp[1024];
    int flag = 1;
    FILE *fi = fopen("D:\\Works\\C\\DS\\009\\009_i.txt", "r");
    while (flag)
    {
        fpos_t pos;
        int i;
        for (i = 0; i < 1024; ++i)
        {
            fgetpos(fi, &pos);
            temp[i] = fgetc(fi);
            if (temp[i] == EOF)
            {
                flag = 0;
                break;
            }
            if (isdigit(temp[i]))
            {
                fsetpos(fi, &pos);
                break;
            }
        }
        if (flag)
        {
            temp[i - 1] = 0;
            int key = 0;
            for (int j = 0; temp[j]; ++j)
            {
                key += temp[j];
            }
            key %= N;
            link *l = &list[key];
            while (l->next)
            {
                l = l->next;
            }
            l->name = malloc(sizeof(char) * strlen(temp));
            strcpy(l->name, temp);

            for (i = 0; i < 1024; ++i)
            {
                temp[i] = fgetc(fi);
                if (temp[i] == '\n')
                {
                    break;
                }
            }
            temp[i] = 0;
            l->num = malloc(sizeof(char) * strlen(temp));
            strcpy(l->num, temp);
            l->next = malloc(sizeof(link));
            l->next->name = l->next->num = (char *)(l->next->next = NULL);
        }
    }
    fclose(fi);

    while (1)
    {
        gets(temp);

        if(!temp[0]){
            break;
        }

        int key = 0;
        for (int i = 0; temp[i]; ++i)
        {
            key += temp[i];
        }
        key %= N;

        link *l = &list[key];
        while (l->next)
        {
            if(!strcmp(l->name, temp)){
                printf("%s ", l->num);
            }
            l = l->next;
        }
        printf("\n");
    }

    return 0;
}