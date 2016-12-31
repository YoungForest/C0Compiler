int list[32];

void sort(int i, int j)
{
    int x, y, z;
    int tmp;

    x = i;
    y = j;
    z = list[(i + j) / 2];
    do
    {
        do
            if (z < list[y])

                y = y - 1;
        while (z < list[y]);

        do
            if (z > list[x])
                x = x + 1;
        while (z > list[x]);

        if (x <= y)
        {
            tmp = list[x];
            list[x] = list[y];
            list[y] = tmp;
            x = x + 1;
            y = y - 1;
        }
    }
    while (x <= y);
    if (x < j) sort(x, j);
    if (i < y) sort(i, y);
}
void endl()
{
    char c;
    c = 10;
    printf(c);
}
void main()
{
    const int top = 20;
    int i;
    list[0] = 123;
    list[1] = -23;
    list[2] = top - 16;
    list[3] = 23;
    list[4] = --35 - top;
    list[5] = + -4;
    list[6] = 4 + 2;
    list[7] = -3;
    list[8] = top + 3;
    list[9] = 103 + top;
    list[10] = -23;
    list[11] = 4;
    list[12] = 23;
    list[13] = 5;
    list[14] = + -4;
    list[15] = 4 + 2;
    list[16] = -3;
    list[17] = 23;
    list[18] = 123;
    list[19] = -23;
    list[20] = 4;
    printf("before : ");
    for (i = 0; i < top + 1; i = i + 1)
        printf(" ", list[i]);
    endl();
    sort(0, top);
    printf("after : ");
    for (i = 0; i < top + 1; i = i + 1)
        printf(" ", list[i]);
}
