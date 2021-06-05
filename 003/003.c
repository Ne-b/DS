#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define L 1024

#define FILE_IN "in.txt"
#define FILE_OUT "out.txt"

void f(char *s)
{
    for (int i = 0; s[i]; ++i)
    {
        if (s[i] == '-' && !isdigit(s[i - 1]) && s[i - 1] != ')')
        {
            int l = strlen(s) + 3, j;
            for (j = i + 1; isdigit(s[j]); ++j)
            {
                continue;
            }
            while (l - 3 >= j)
            {
                s[l] = s[l - 3];
                --l;
            }
            s[l--] = ')';
            while(l - 2 >= i){
                s[l] = s[l - 2];
                --l;
            }
            s[l--] = '0';
            s[l] = '(';
            i += 2;
        }
    }
}

int cmp(char c1, char c2)
{
    switch (c1)
    {
    case '+':
    case '-':
        switch (c2)
        {
        case '+':
        case '-':
        case ')':
        case '#':
            return 1;
        case '*':
        case '/':
        case '^':
        case '(':
            return -1;
        }
    case '*':
    case '/':
        switch (c2)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case ')':
        case '#':
            return 1;
        case '^':
        case '(':
            return -1;
        }
    case '^':
        switch (c2)
        {
        case ')':
            return -1;
        default:
            return 1;
        }
    case '(':
        switch (c2)
        {
        case ')':
            return 0;
        default:
            return -1;
        }
    case ')':
        return 1;
    case '#':
        switch (c2)
        {
        case '#':
            return 0;
        default:
            return -1;
        }
    }
}

int operate(int a, int b, char c)
{
    switch (c)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return (int)pow(a, b);
    }
}

int main()
{
    FILE *ip = fopen(FILE_IN, "r");
    char expression[L];
    fgets(expression, L, ip);
    f(expression);
    expression[strlen(expression) - 1] = '#';
    fclose(ip);

    char sym[L];
    int num[L] = {0};
    sym[0] = '#';

    int flag = 0;
    for (int i = 0, n = 0, s = 0; expression[i]; ++i)
    {
        if (isdigit(expression[i]))
        {
            num[n] = num[n] * 10 + expression[i] - '0';
            flag = 1;
        }
        else
        {
            if (flag)
            {
                ++n;
                flag = 0;
            }
            int temp = cmp(sym[s], expression[i]);
            if (temp < 0)
            {
                sym[++s] = expression[i];
            }
            else if (temp > 0)
            {
                num[n - 2] = operate(num[n - 2], num[n - 1], sym[s--]);
                num[--n] = 0;
                --i;
            }
            else
            {
                s--;
            }
        }
    }

    FILE *op = fopen(FILE_OUT, "w");
    fprintf(op, "%d\n", num[0]);
    fclose(op);

    return 0;
}
