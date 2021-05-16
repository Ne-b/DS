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
    //������m���� ÿ����n��
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
    //ÿ���Ӧһֻδ�뿪�ĺ��ӣ�iΪ���ӱ��-1

    //��ǰӦ��nowָ��ĺ��ӿ�ʼ��
    while(now->next != now){
        //��ʣ���������Ψһʱ
        for(int i = 0; i < n; ++i){
            now = now->next;
        }
        delmk(&now);
        //�������ĺ����뿪
    }

    fprintf(f, "��%dֻ����Ϊ������\n", now->i + 1);

    return 0;
}
