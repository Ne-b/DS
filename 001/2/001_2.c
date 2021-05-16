#include <stdio.h>
#include <stdlib.h>

typedef struct monkey{
    struct monkey * before;
    int i;
    struct monkey * next;
}mk;

void newmk(mk * now, int i){
    now->next = malloc(sizeof(mk));
    now->next->before = now;
    now->next->i = i;
    now->next->next = NULL;
}

void delmk(mk ** now){
    (*now)->before->next = (*now)->next;
    (*now)->next->before = (*now)->before;
    mk * temp = *now;
    *now = (*now)->before;
    free(temp);
}

int main()
{
    FILE * f = fopen("D:\\Works\\C\\DS\\001\\2\\001_2_o.txt", "w");
    int m, n;
    //猴子有m个， 每次数n个
    FILE * t = fopen("D:\\Works\\C\\DS\\001\\2\\001_2_i.txt", "r");
    fscanf(t, "%d %d", &m, &n);
    fclose(t);

    mk * head = malloc(sizeof(mk));
    head->i = 0;
    mk * now = head;
    for(int i = 1; i < m; ++i){
        newmk(now, i);
        now = now->next;
    }
    now->next = head;
    now->next->before = now;
    //每项对应一只未离开的猴子，i为猴子编号-1

    //当前应从now指向的猴子开始数
    while(now->next != now){
        //当剩余猴子数不唯一时
        for(int i = 0; i < n; ++i){
            now = now->next;
        }
        delmk(&now);
        //被数到的猴子离开
    }

    fprintf(f, "第%d只猴子为猴王。\n", now->i + 1);

    return 0;
}
