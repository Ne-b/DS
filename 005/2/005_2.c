#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1024

#define FILE_IN stdin
#define FILE_OUT stdout

typedef struct nodes
{
    struct nodes *left;
    char *i;
    struct nodes *right;
} node;

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

node *search_add(node *root, char *i)
{
    while (1)
    {
        if (strcmp(root->i, i) < 0)
        {
            if (root->right)
            {
                root = root->right;
            }
            else
            {
                return root;
            }
        }
        else
        {
            if (root->left)
            {
                root = root->left;
            }
            else
            {
                return root;
            }
        }
    }
}

int max_depth(node *root)
{
    if (root)
    {
        int max_left = max_depth(root->left);
        int max_right = max_depth(root->right);
        return 1 + (max_left > max_right ? max_left : max_right);
    }
    else
    {
        return 0;
    }
}

int is_balanced(node *root)
{
    if (root)
    {
        if (is_balanced(root->left) && is_balanced(root->right))
        {
            int left_depth = max_depth(root->left);
            int right_depth = max_depth(root->right);
            if (left_depth - right_depth > 1 || right_depth - left_depth > 1)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 1;
    }
}

node *min_unbalanced_subtree(node *root)
{
    if (!root || is_balanced(root))
    {
        return NULL;
    }
    else
    {
        if (is_balanced(root->left))
        {
            if (is_balanced(root->right))
            {
                return root;
            }
            else
            {
                return min_unbalanced_subtree(root->right);
            }
        }
        else
        {
            return min_unbalanced_subtree(root->left);
        }
    }
}

int search(node *root, node *p)
{
    if (p)
    {
        if (root)
        {
            if (root == p)
            {
                return 1;
            }
            else
            {
                return search(root->left, p) || search(root->right, p);
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int which(node *root, node *p)
{
    if (root->left)
    {
        if (root->left->left && search(root->left->left, p))
        {
            return 1;
        }
        else if (root->left->right && search(root->left->right, p))
        {
            return 2;
        }
    }
    if (root->right)
    {
        if (root->right->left && search(root->right->left, p))
        {
            return 3;
        }
        else if (root->right->right && search(root->right->right, p))
        {
            return 4;
        }
    }
    return 0;
}

void adjust(node *root, int i)
{
    if (i)
    {
        node *p;
        if (i == 1)
        {
            p = root->left;
            root->left = p->left;
            p->left = p->right;
            p->right = root->right;
            root->right = p;
        }
        else if (i == 2)
        {
            p = root->left->right;
            root->left->right = p->left;
            p->left = p->right;
            p->right = root->right;
            root->right = p;
        }
        else if (i == 3)
        {
            p = root->right->left;
            root->right->left = p->right;
            p->right = p->left;
            p->left = root->left;
            root->left = p;
        }
        else if (i == 4)
        {
            p = root->right;
            root->right = p->right;
            p->right = p->left;
            p->left = root->left;
            root->left = p;
        }
        char *temp = malloc(sizeof(char) * (strlen(root->i) + 1));
        strcpy(temp, root->i);
        free(root->i);
        root->i = malloc(sizeof(char) * (strlen(p->i) + 1));
        strcpy(root->i, p->i);
        free(p->i);
        p->i = malloc(sizeof(char) * (strlen(temp) + 1));
        strcpy(p->i, temp);
        free(temp);
    }
}

int main()
{
    FILE *fi = fopen(FILE_IN, "r");
    node *root = malloc(sizeof(node));
    root->left = root->right = NULL;
    char *i = malloc(sizeof(char) * MAX);
    fgets(i, MAX, fi);
    i[strlen(i) - 1] = 0;
    root->i = malloc(sizeof(char) * (strlen(i) + 1));
    strcpy(root->i, i);
    while (fi->_base != fi->_ptr)
    {
        fgets(i, MAX, fi);
        i[strlen(i) - 1] = 0;
        if (strlen(i))
        {
            node *temp = search_add(root, i);
            if (strcmp(temp->i, i) < 0)
            {
                temp->right = malloc(sizeof(node));
                temp = temp->right;
            }
            else
            {
                temp->left = malloc(sizeof(node));
                temp = temp->left;
            }
            temp->left = temp->right = NULL;
            temp->i = malloc(sizeof(char) * (strlen(i) + 1));
            strcpy(temp->i, i);
            node *unbalanced = min_unbalanced_subtree(root);
            if(unbalanced){
                adjust(unbalanced, which(unbalanced, temp));
            }
        }
    }
    fclose(fi);

    FILE *fo = fopen(FILE_OUT, "w");
    fprintf(fo, "dlr: ");
    print_dlr_r(fo, root);
    fprintf(fo, "\nldr: ");
    print_ldr_r(fo, root);
    fprintf(fo, "\nlrd: ");
    print_lrd_r(fo, root);
    fclose(fo);

    return 0;
}
