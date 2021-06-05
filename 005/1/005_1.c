#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

#define FILE_IN "in.txt"
#define FILE_OUT "out.txt"

// recursive 递归
// iteration 迭代

typedef struct nodes
{
    struct nodes *left;
    char *i;
    struct nodes *right;
} node;

void creat(node **n, FILE *fi)
{
    char *i = malloc(sizeof(char) * MAX);
    fgets(i, MAX, fi);
    i[strlen(i) - 1] = 0;
    if (strlen(i) && fi->_ptr != fi->_base)
    {
        *n = malloc(sizeof(node));
        (*n)->i = malloc(sizeof(char) * (strlen(i) + 1));
        strcpy((*n)->i, i);
        creat(&(*n)->left, fi);
        creat(&(*n)->right, fi);
    }
    else
    {
        *n = NULL;
    }
}

void print_dlr_r(FILE *f, node *root)
{
    fprintf(f, "%s ", root->i);
    if (root->left)
    {
        print_dlr_r(f, root->left);
    }
    if (root->right)
    {
        print_dlr_r(f, root->right);
    }
}
void print_ldr_r(FILE *f, node *root)
{
    if (root->left)
    {
        print_ldr_r(f, root->left);
    }
    fprintf(f, "%s ", root->i);
    if (root->right)
    {
        print_ldr_r(f, root->right);
    }
}
void print_lrd_r(FILE *f, node *root)
{
    if (root->left)
    {
        print_lrd_r(f, root->left);
    }
    if (root->right)
    {
        print_lrd_r(f, root->right);
    }
    fprintf(f, "%s ", root->i);
}

void print_dlr_i(FILE *f, node *root)
{
    struct
    {
        node *left;
        char *i;
        node *right;
    } s[MAX];
    int now = 0;
    s[now].left = root->left;
    s[now].i = root->i;
    s[now].right = root->right;

    while (now >= 0)
    {
        node *temp = malloc(sizeof(node));
        temp->left = s[now].left;
        temp->i = s[now].i;
        temp->right = s[now].right;
        --now;
        fprintf(f, "%s ", temp->i);
        if (temp->right)
        {
            ++now;
            s[now].left = temp->right->left;
            s[now].i = temp->right->i;
            s[now].right = temp->right->right;
        }
        if (temp->left)
        {
            ++now;
            s[now].left = temp->left->left;
            s[now].i = temp->left->i;
            s[now].right = temp->left->right;
        }
    }
}
void print_ldr_i(FILE *f, node *root)
{
    struct
    {
        int flag;
        node *left;
        char *i;
        node *right;
    } s[MAX];
    int now = 0;
    s[now].flag = 0;
    s[now].left = root->left;
    s[now].i = root->i;
    s[now].right = root->right;

    while (now >= 0)
    {
        node *temp = malloc(sizeof(node));
        int flag = s[now].flag;
        temp->left = s[now].left;
        temp->i = s[now].i;
        temp->right = s[now].right;
        --now;
        if (flag)
        {
            fprintf(f, "%s ", temp->i);
        }
        else
        {
            if (temp->right)
            {
                ++now;
                s[now].flag = 0;
                s[now].left = temp->right->left;
                s[now].i = temp->right->i;
                s[now].right = temp->right->right;
            }
            ++now;
            s[now].flag = 1;
            s[now].left = temp->left;
            s[now].i = temp->i;
            s[now].right = temp->right;
            if (temp->left)
            {
                ++now;
                s[now].flag = 0;
                s[now].left = temp->left->left;
                s[now].i = temp->left->i;
                s[now].right = temp->left->right;
            }
        }
    }
}
void print_lrd_i(FILE *f, node *root)
{
    struct
    {
        int flag;
        node *left;
        char *i;
        node *right;
    } s[MAX];
    int now = 0;
    s[now].flag = 0;
    s[now].left = root->left;
    s[now].i = root->i;
    s[now].right = root->right;

    while (now >= 0)
    {
        node *temp = malloc(sizeof(node));
        int flag = s[now].flag;
        temp->left = s[now].left;
        temp->i = s[now].i;
        temp->right = s[now].right;
        --now;
        if (flag)
        {
            fprintf(f, "%s ", temp->i);
        }
        else
        {
            ++now;
            s[now].flag = 1;
            s[now].left = temp->left;
            s[now].i = temp->i;
            s[now].right = temp->right;
            if (temp->right)
            {
                ++now;
                s[now].flag = 0;
                s[now].left = temp->right->left;
                s[now].i = temp->right->i;
                s[now].right = temp->right->right;
            }
            if (temp->left)
            {
                ++now;
                s[now].flag = 0;
                s[now].left = temp->left->left;
                s[now].i = temp->left->i;
                s[now].right = temp->left->right;
            }
        }
    }
}

int print_hierarchy(FILE *f, node *root)
{
    int height = 0;
    typedef struct queue
    {
        node *left;
        char *i;
        node *right;
        struct queue *next;
    } q;
    q *q1 = malloc(sizeof(q));
    q *q2 = malloc(sizeof(q));
    q1->left = q1->right = (node *)(q1->i = NULL);
    q2->left = q2->right = (node *)(q2->i = (char *)(q2->next = NULL));

    q1->next = malloc(sizeof(q));
    q1->next->left = root->left;
    q1->next->i = root->i;
    q1->next->right = root->right;
    q1->next->next = NULL;

    while (q1->next || q2->next)
    {
        q *temp;
        if (++height % 2)
        {
            temp = q2;
            while (q1->next)
            {
                int flag = 0;
                temp->next = malloc(sizeof(q));
                temp = temp->next;
                temp->next = NULL;
                if (q1->next->left)
                {
                    temp->left = q1->next->left->left;
                    temp->i = q1->next->left->i;
                    temp->right = q1->next->left->right;
                    temp->next = malloc(sizeof(q));
                    temp = temp->next;
                    temp->next = NULL;
                }
                if (q1->next->right)
                {
                    temp->left = q1->next->right->left;
                    temp->i = q1->next->right->i;
                    temp->right = q1->next->right->right;
                    temp->next = NULL;
                    flag = 1;
                }
                fprintf(f, "%s ", q1->next->i);
                if (!flag)
                {
                    temp = q2;
                    while (temp->next->next)
                    {
                        temp = temp->next;
                    }
                    free(temp->next);
                    temp->next = NULL;
                }
                temp = q1;
                q1 = q1->next;
                free(temp);
                temp = q2;
                while (temp->next)
                {
                    temp = temp->next;
                }
            }
        }
        else
        {
            temp = q1;
            while (q2->next)
            {
                int flag = 0;
                temp->next = malloc(sizeof(q));
                temp = temp->next;
                temp->next = NULL;
                if (q2->next->left)
                {
                    temp->left = q2->next->left->left;
                    temp->i = q2->next->left->i;
                    temp->right = q2->next->left->right;
                    temp->next = malloc(sizeof(q));
                    temp = temp->next;
                    temp->next = NULL;
                }
                if (q2->next->right)
                {
                    temp->left = q2->next->right->left;
                    temp->i = q2->next->right->i;
                    temp->right = q2->next->right->right;
                    temp->next = NULL;
                    flag = 1;
                }
                fprintf(f, "%s ", q2->next->i);
                if (!flag)
                {
                    temp = q1;
                    while (temp->next->next)
                    {
                        temp = temp->next;
                    }
                    free(temp->next);
                    temp->next = NULL;
                }
                temp = q2;
                q2 = q2->next;
                free(temp);
                temp = q1;
                while (temp->next)
                {
                    temp = temp->next;
                }
            }
        }
        fprintf(f, "\n\t");
    }
    return height;
}

int main()
{
    FILE *fi = fopen(FILE_IN, "r");

    node *root;
    creat(&root, fi);

    fclose(fi);

    FILE *fo = fopen(FILE_OUT, "w");

    fprintf(fo, "recursive: \n\tdlr: ");
    print_dlr_r(fo, root);
    fprintf(fo, "\n\tldr: ");
    print_ldr_r(fo, root);
    fprintf(fo, "\n\tlrd: ");
    print_lrd_r(fo, root);
    fprintf(fo, "\n\t\n");

    fprintf(fo, "iteration: \n\tdlr: ");
    print_dlr_i(fo, root);
    fprintf(fo, "\n\tldr: ");
    print_ldr_i(fo, root);
    fprintf(fo, "\n\tlrd: ");
    print_lrd_i(fo, root);
    fprintf(fo, "\n\t\n");

    fprintf(fo, "hierarchy: \n\t");
    int height = print_hierarchy(fo, root);
    fprintf(fo, "\nheight: \n\t");
    fprintf(fo, "%d\n\t", height);

    fclose(fo);

    return 0;
}
