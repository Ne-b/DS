#include <stdio.h>
#include <stdlib.h>

int sum(int *mk, int m)
{
    //��ͼ��õ�ǰʣ�������
    int sum = 0;
    for (int i = 0; i < m; ++i)
    {
        sum += mk[i];
    }
    return sum;
}

int main()
{
    FILE *f = fopen("D:\\Works\\C\\DS\\001\\1\\001_1_o.txt", "w");

    int m, n;
    //������m���� ÿ����n��
    FILE * t = fopen("D:\\Works\\C\\DS\\001\\1\\001_1_i.txt", "r");
    fscanf(t, "%d %d", &m, &n);
    fclose(t);
    int *mk = malloc(sizeof(int) * m);
    for (int i = 0; i < m; ++i)
    {
        mk[i] = 1;
    }
    //ÿ���Ӧһֻ���ӣ�1����δ�뿪��0�����뿪
    int now = 0;
    //��ǰӦ�ӵ�nowֻ���ӿ�ʼ��
    int i = 0;
    while (sum(mk, m) != 1)
    {
        //��ʣ���������Ψһʱ
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

        //�������ĺ����뿪
    }

    for (int i = 0; i < m; ++i)
    {
        if (mk[i])
        {
            fprintf(f, "��%dֻ����Ϊ������\n", i + 1);
            fclose(f);
            break;
        }
    }
    free(mk);

    return 0;
}
