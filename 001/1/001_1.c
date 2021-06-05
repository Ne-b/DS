#include <stdio.h>
#include <stdlib.h>

#define FILE_IN "in.txt"
#define FILE_OUT "out.txt"

int sum(int *mk, int m)
{
    //求和即得当前剩余猴子数
    int sum = 0;
    for (int i = 0; i < m; ++i)
    {
        sum += mk[i];
    }
    return sum;
}

int main()
{
    FILE *f = fopen(FILE_OUT, "w");

    int m, n;
    //猴子有m个， 每次数n个
    FILE * t = fopen(FILE_IN, "r");
    fscanf(t, "%d %d", &m, &n);
    fclose(t);
    int *mk = malloc(sizeof(int) * m);
    for (int i = 0; i < m; ++i)
    {
        mk[i] = 1;
    }
    //每项对应一只猴子，1代表未离开，0代表离开
    int now = 0;
    //当前应从第now只猴子开始数
    int i = 0;
    while (sum(mk, m) != 1)
    {
        //当剩余猴子数不唯一时
        if (mk[now])
        {
            ++i;
        }
        if (!(i % n))
        {
            mk[now] = 0;
        }
        ++now;
        now %= m;

        //被数到的猴子离开
    }

    for (int i = 0; i < m; ++i)
    {
        if (mk[i])
        {
            fprintf(f, "第%d只猴子为猴王。\n", i + 1);
            fclose(f);
            break;
        }
    }
    free(mk);

    return 0;
}
