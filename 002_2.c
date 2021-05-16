#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct variable
{
    char var;
    int exponent;
    struct variable *next;
} var;

typedef struct polynomial
{
    float coefficient;
    var *v;
    struct polynomial *next;
} poly;
///新建节点
poly *creatpoly()
{
    poly *p = malloc(sizeof(poly));
    p->coefficient = 0.;
    p->v = NULL;
    p->next = NULL;
    return p;
}
///新建变量
var *creatvar()
{
    var *v = malloc(sizeof(var));
    v->var = 0;
    v->exponent = 0;
    v->next = NULL;
    return v;
}
///输入多项式
poly *newpoly(FILE **f)
{
    poly *head = creatpoly(), *p = head;
    char temp[1024];
    while (1)
    {
        p->next = creatpoly();
        p = p->next;
        fscanf(*f, "%s", temp);
        fgetc(*f);
        if (!strcmp(temp, "0"))
        {
            return head;
        }
        p->coefficient = atof(temp);
        char c;
        int d;
        var *t = p->v = creatvar();
        while (1)
        {
            fscanf(*f, "%c %d", &c, &d);
            t->var = c;
            t->exponent = d;
            t->next = creatvar();
            t = t->next;
            if (fgetc(*f) == '\n')
            {
                break;
            }
        }
    }
}
///打印
void print(poly *head, FILE **f)
{
    head = head->next;
    if (!(head->next))
    {
        fprintf(*f, "\n0\n");
        return;
    }
    while (head->next)
    {
        fprintf(*f, "\n%g ", head->coefficient);
        var * t = head->v;
        while(t->next){
            fprintf(*f, "%c %d ", t->var, t->exponent);
            t = t->next;
        }
        head = head->next;
    }
    fprintf(*f, "\n");
}
///单项比较
int cmp(poly *p1, poly *p2)
{
    var *v1 = p1->v, *v2 = p2->v;
    while ((v1->var == v2->var) && (v1->exponent == v2->exponent))
    {
        if (v1->var == 0)
        {
            return 1;
        }
        v1 = v1->next;
        v2 = v2->next;
    }
    return 0;
}
///加法
poly *add(poly *head1, poly *head2)
{
    poly *p1 = head1->next, *p2 = head2->next;
    while (p1->next)
    {
        int flag = 0;
        while (p2->next)
        {
            if (cmp(p1, p2))
            {
                p2->coefficient += p1->coefficient;
                flag = 1;
                break;
            }
            p2 = p2->next;
        }
        if (!flag)
        {
            p2 = head2->next;
            head2->next = p1;
            p1 = p1->next;
            head2->next->next = p2;
        }
        else
        {
            p1 = p1->next;
        }
        p2 = head2->next;
    }

    return head2;
}

int main()
{
    FILE *f = fopen("D:\\Works\\C\\DS\\002\\2\\002_2_o.txt", "w");
    FILE *t = fopen("D:\\Works\\C\\DS\\002\\2\\002_2_i.txt", "r");

    poly *head1 = newpoly(&t);
    poly *head2 = newpoly(&t);

    poly *a = add(head1, head2);
    print(a, &f);

    return 0;
}