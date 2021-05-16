#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct words
{
    char *word;
    int n;
    int position[2];
    struct words *next;
} word;

word *creat(char *w, int x, int y)
{
    if(w && !w[0]){
        return NULL;
    }
    word *temp = malloc(sizeof(word));
    if (w == NULL)
    {
        temp->word = NULL;
        temp->n = 0;
    }
    else
    {
        temp->word = malloc(sizeof(char) * (strlen(w) + 1));
        strcpy(temp->word, w);
        temp->n = 1;
    }
    temp->position[0] = x;
    temp->position[1] = y;
    temp->next = NULL;
    return temp;
}

char * input(FILE *f, char *word)
{
    char *c = malloc(sizeof(char) * 2);
    int i = 0;
    while (isalnum(c[1] = fgetc(f)) || c[1] == '-' || c[1] == '\'')
    {
        word[i++] = c[1];
    }
    word[i] = 0;
    c[0] = word[i - 1];
    for(int i = 0; word[i]; ++i){
        word[i] = tolower(word[i]);
    }
    return c;
}

void add(word * head, char * w, int x, int y){
    while(head->next){
        if(!strcmp(head->next->word, w)){
            ++head->next->n;
            return;
        }
        head = head->next;
    }
    head->next = creat(w, x, y);
}

void printmin(FILE * fo, word * head, float total, int l){
    word * p = head->next, * bp = head, * minp = head->next, * bminp = head;;
    char * min = p->word;
    while(p){
        if(strcmp(p->word, min) < 0){
            min = p->word;
            minp = p;
            bminp = bp;
        }
        p = p->next;
        bp = bp->next;
    }
    fprintf(fo, "%s", minp->word);
    for(int i = 0; i <= l - strlen(minp->word) / 4; ++i){
        fprintf(fo, "\t");
    }
    fprintf(fo, "次数：%3d\t频度：%.4f\t行号：%3d\t位置：%3d\n", minp->n, minp->n / total, minp->position[0], minp->position[1]);
    bminp->next = minp->next;
    free(minp);
}

int main()
{
    FILE *fi = fopen("D:\\Works\\C\\DS\\004\\004_i.txt", "r");
    word *head = creat(NULL, 0, 0);
    char w[100], *c, x = 1, y = 1;
    while (1)
    {
        c = input(fi, w);
        add(head, w, x, y);
        if(c[1] == '\n'){
            y = 1;
            ++x;
        }
        else if(isalnum(c[0]) && !isalnum(c[1])){
            ++y;
        }
        else if(c[1] == EOF){
            break;
        }
    }
    fclose(fi);

    word * p = head->next;
    float total = 0.;
    int l = strlen(p->word);
    while(p){
        int t = strlen(p->word);
        if(t > l){
            l = t;
        }
        total += p->n;
        p = p->next;
    }

    FILE *fo = fopen("D:\\Works\\C\\DS\\004\\004_o.txt", "w");
    while(head->next){
        printmin(fo, head, total, l / 4);
    }
    fclose(fo);

    return 0;
}
