#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///单项节点
typedef struct polynomial
{
    float coefficient; ///系数
    int exponent;      ///次数
    struct polynomial *next;
} poly;
///新建节点
poly *creat()
{
    poly *p = malloc(sizeof(poly));
    p->exponent = 0;
    p->coefficient = 0.;
    p->next = NULL;
    return p;
}
///降幂排序
poly *sort(poly *head)
{
    poly *p = head->next, *temp = head;
    while (temp->next->next)///temp不是最后一项时
    {
        poly *max = p;
        p = p->next;
        while (p->next)
        {
            if (p->exponent > max->exponent)
            {
                max = p;
            }
            p = p->next;
        }///找到次数最大项

        float t1 = max->coefficient;
        max->coefficient = temp->next->coefficient;
        temp->next->coefficient = t1;

        int t2 = max->exponent;
        max->exponent = temp->next->exponent;
        temp->next->exponent = t2;
        ///交换节点内容使最大项前移
        temp = temp->next;
        p = temp->next;
    }
    return head;
}
///输入多项式
poly *newpoly(FILE **f)
{
    poly *head = creat(), *p = head;
    char temp[1024];///缓冲区
    while (1)
    {
        p->next = creat();
        p = p->next;
        fscanf(*f, "%s", temp);
        if (!strcmp(temp, "0"))///系数为零停止输入
        {
            return sort(head);
        }
        p->coefficient = atof(temp);
        fscanf(*f, "%s", temp);
        p->exponent = atoi(temp);
    }
}
///打印
void print(poly *head, FILE **f)
{
    fprintf(*f, "\n");
    head = head->next;
    if (!(head->next))///多项式没有项打印零
    {
        fprintf(*f, "0\n");
        return;
    }
    while (head->next)
    {
        fprintf(*f, "%g %d\n", head->coefficient, head->exponent);
        head = head->next;
    }
}
///加法
poly *add(poly *head1, poly *head2)
{
    poly *p1 = head1->next, *p2 = head2->next, *head3 = creat(), *p3 = head3;
    while (p1->next && p2->next)
    {
        p3->next = creat();
        if (p1->exponent > p2->exponent)
        {
            p3->next->coefficient = p1->coefficient;
            p3->next->exponent = p1->exponent;
            p1 = p1->next;
        }
        else if (p1->exponent < p2->exponent)
        {
            p3->next->coefficient = p2->coefficient;
            p3->next->exponent = p2->exponent;
            p2 = p2->next;
        }
        else
        {
            p3->next->coefficient = p1->coefficient + p2->coefficient;
            p3->next->exponent = p1->exponent;
            p1 = p1->next;
            p2 = p2->next;
        }
        p3 = p3->next;
    }
    while (p1->next)///p1余项连接到结果链表
    {
        p3->next = creat();
        p3->next->coefficient = p1->coefficient;
        p3->next->exponent = p1->exponent;
        p1 = p1->next;
        p3 = p3->next;
    }
    while (p2->next)///p2余项连接到结果链表
    {
        p3->next = creat();
        p3->next->coefficient = p2->coefficient;
        p3->next->exponent = p2->exponent;
        p2 = p2->next;
        p3 = p3->next;
    }
    p3->next = creat();///使结果标准化
    p3 = head3;
    poly *p = head3;
    while (p3->next)
    {
        p3 = p3->next;
        if (!(p3->coefficient) && p3->next)///清除零项
        {
            p->next = p3->next;
            free(p3);
            p3 = p;
            continue;
        }
        p = p->next;
    }
    return head3;
}
///减法
poly *sub(poly *head1, poly *head2)
{
    poly *temp = creat(), *h = temp;

    while (head2->next)///得到 h = -head2
    {
        temp->coefficient = -head2->coefficient;
        temp->exponent = head2->exponent;
        temp->next = creat();
        temp = temp->next;
        head2 = head2->next;
    }
    return add(head1, h);///调用加法
}
///单项乘法
poly *mul_one(poly *p1, poly *p2)
{
    poly *p3 = creat();
    p3->coefficient = p1->coefficient * p2->coefficient;
    p3->exponent = p1->exponent + p2->exponent;
    return p3;
}
///合并同类项
poly *trim(poly *head)
{
    poly *p = head->next;
    while (p->next)
    {
        poly *temp = p, *pt = temp;
        while (temp->next)
        {
            temp = temp->next;
            if (p->exponent == temp->exponent && (temp->coefficient || temp->exponent))///次数相同项合并
            {
                p->coefficient += temp->coefficient;
                pt->next = temp->next;
                free(temp);
                temp = pt;
                continue;
            }
            pt = pt->next;
        }
        p = p->next;
    }
    return head;
}
///乘法
poly *mul(poly *head1, poly *head2)
{
    poly *p1 = head1->next, *p2 = head2->next, *head3 = creat(), *p3 = head3;
    while (p1->next)///保存每个单项相乘结果
    {
        while (p2->next)
        {
            p3->next = mul_one(p1, p2);
            p2 = p2->next;
            p3 = p3->next;
        }
        p1 = p1->next;
        p2 = head2->next;
    }
    p3->next = creat();
    return sort(trim(head3));///对结果合并同类项并排序
}
///单项除法
poly *divide_one(poly *p1, poly *p2)
{
    poly *p3 = creat();
    p3->coefficient = p1->coefficient / p2->coefficient;
    p3->exponent = p1->exponent - p2->exponent;
    p3->next = creat();
    return p3;
}
///除法
poly *divide(poly *head1, poly *head2)
{
    poly *p1, *p2, *head3 = creat(), *p3 = head3;
    while (1)
    {
        p1 = head1->next;
        p2 = head2->next;
        p3->next = divide_one(p1, p2);
        head1 = sub(head1, mul(head2, p3));
        if (!head1->next->next)
        {
            return head3;
        }
        if (head1->next->exponent < head2->next->exponent)
        {
            return NULL;
        }
        p3 = p3->next;
    }
}

int main()
{
    FILE *f = fopen("D:\\Works\\C\\DS\\002\\1\\002_1_o.txt", "w");
    FILE *t = fopen("D:\\Works\\C\\DS\\002\\1\\002_1_i.txt", "r");

    poly *head1 = newpoly(&t);
    poly *head2 = newpoly(&t);

    poly *a = add(head1, head2);
    print(a, &f);

    poly *s = sub(head1, head2);
    print(s, &f);

    poly *m = mul(head1, head2);
    print(m, &f);

    poly *d = divide(head1, head2);
    if (d)
    {
        print(d, &f);
    }
    else
    {
        fprintf(f, "\n不能整除\n");
    }

    fclose(t);
    fclose(f);

    return 0;
}