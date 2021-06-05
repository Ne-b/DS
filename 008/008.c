#include <stdio.h>
#include <stdlib.h>

#define FILE_IN "in.txt"
#define FILE_OUT "out.txt"

void screen(int *num, int n, int i)
{
    while (2 * i < n)
    {
        if (num[i] > num[2 * i] && num[2 * i] < num[2 * i + 1])
        {
            num[i] ^= num[2 * i];
            num[2 * i] ^= num[i];
            num[i] ^= num[2 * i];
            i *= 2;
        }
        else if (num[i] > num[2 * i + 1])
        {
            num[i] ^= num[2 * i + 1];
            num[2 * i + 1] ^= num[i];
            num[i] ^= num[2 * i + 1];
            i = 2 * i + 1;
        }
        else
        {
            break;
        }
    }
}

int main()
{
    FILE *fi = fopen(FILE_IN, "r");
    char c;
    int n = 0;
    while ((c = fgetc(fi)) != EOF)
    {
        if (c == '\n')
        {
            ++n;
        }
    }
    rewind(fi);
    int *num = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
    {
        fscanf(fi, "%d ", &num[i]);
    }
    fclose(fi);

    for (int i = n / 2; i >= 0; --i)
    {
        screen(num, n, i);
    }

    FILE * fo = fopen(FILE_OUT, "w");
    for (int i = 1; i <= n; ++i){
        fprintf(fo, "%d ", num[0]);
        num[0] = num[n - i];
        screen(num, n - i, 0);
    }
    fclose(fo);

    return 0;
}
