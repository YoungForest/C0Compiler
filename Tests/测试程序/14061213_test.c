const int MAX = 126, MIN = 32, gap = 34;
const char add = '+', sub = '-', multi = '*', slash = '/';
int list[32];
int array[100], i, j;
int k;
char ch, set[26];
char h;

void endl()
{
    char c;
    c = 10;
    printf(c);
}

int func_2_number(int a, int b)
{
    const int ten = 10;
    char zero;
    int r;

    zero = '0';
    r = a * ten + b;

    return (r);
}

void putchar(char ch)
{
    printf(ch);
}
int fibonacci(int n)
{
    if(n >= 0)
        if(n <= 1)
            return (1);
        else
            return (fibonacci(n-1) + fibonacci(n-2));
    else
        return (0);
}

void func()
{
    int ch, j, k, i;
    i = 100;
    j = 40;
    k = 20;
    printf(i*(- func_2_number(j, 20) + k) * (j / k));
    putchar('_');
    ch = '/';
    if( ch + 10 < MAX)
        if( ch + 10 != MIN)
            if (ch - 5 > MIN)
                if (ch - 4 >= MIN)
                    if (ch + 15 <= MAX)
                        if(ch + 10 != gap)
                            if (ch)
                                if (ch == 47)
                                    if (ch == '/')
                                        printf(ch - 10);
}
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
void main()
{
    const int top = 12; 
    const int top2 = 20;
    int f;
    int x;
    char _abcdefghigklmnopqrstuvwxyz[36];
    
    for(i = 0; i < 26; i=i+1)
    {
        _abcdefghigklmnopqrstuvwxyz[i] = 'A' + i;
        putchar(_abcdefghigklmnopqrstuvwxyz[i]);
        printf(i);
    }
    putchar('_');
    _abcdefghigklmnopqrstuvwxyz[1] = 'B';
    _abcdefghigklmnopqrstuvwxyz[2] = 'C';
    _abcdefghigklmnopqrstuvwxyz[3] = 'D';
    _abcdefghigklmnopqrstuvwxyz[4] = 'E';
    _abcdefghigklmnopqrstuvwxyz[5] = 'F';
    _abcdefghigklmnopqrstuvwxyz[6] = 'G';
    _abcdefghigklmnopqrstuvwxyz[7] = 'H';
    _abcdefghigklmnopqrstuvwxyz[8] = 'I';
    _abcdefghigklmnopqrstuvwxyz[9] = 'J';
    _abcdefghigklmnopqrstuvwxyz[10] = 'K';
    _abcdefghigklmnopqrstuvwxyz[11] = 'L';
    _abcdefghigklmnopqrstuvwxyz[12] = 'M';
    _abcdefghigklmnopqrstuvwxyz[13] = 'N';
    _abcdefghigklmnopqrstuvwxyz[14] = 'O';
    _abcdefghigklmnopqrstuvwxyz[15] = 'P';
    _abcdefghigklmnopqrstuvwxyz[16] = 'Q';
    _abcdefghigklmnopqrstuvwxyz[17] = 'R';
    _abcdefghigklmnopqrstuvwxyz[18] = 'S';
    _abcdefghigklmnopqrstuvwxyz[19] = 'T';
    _abcdefghigklmnopqrstuvwxyz[20] = 'U';
    _abcdefghigklmnopqrstuvwxyz[21] = 'V';
    _abcdefghigklmnopqrstuvwxyz[22] = 'W';
    _abcdefghigklmnopqrstuvwxyz[23] = 'L';
    _abcdefghigklmnopqrstuvwxyz[24] = 'Y';
    _abcdefghigklmnopqrstuvwxyz[25] = 'Z';
    _abcdefghigklmnopqrstuvwxyz[26] = '0';
    _abcdefghigklmnopqrstuvwxyz[27] = '1';
    _abcdefghigklmnopqrstuvwxyz[28] = '2';
    _abcdefghigklmnopqrstuvwxyz[29] = '3';
    _abcdefghigklmnopqrstuvwxyz[30] = '4';
    _abcdefghigklmnopqrstuvwxyz[31] = '5';
    _abcdefghigklmnopqrstuvwxyz[32] = '6';
    _abcdefghigklmnopqrstuvwxyz[33] = '7';
    _abcdefghigklmnopqrstuvwxyz[34] = '8';
    _abcdefghigklmnopqrstuvwxyz[35] = '9';
    for(i = 26; i <= 35; i=i+1)
    {
        putchar(_abcdefghigklmnopqrstuvwxyz[i]);
        printf(i);
    }

    {}
    f = 0;
    do
    {
        f = f + 5;
        printf("The number of 'f*10' is:", f * 10);
        putchar('_');
    }
    while(f < top)

    scanf(i, j, k, ch);
    printf("The first number you input is ");
    printf(i);
    printf("Its fibonacci is ");
    printf(fibonacci(i));
    putchar('_');
    endl();
    do
    {
        printf("More number? (0 to end) : ");
        scanf(i);
        printf("Fibonacci : ", fibonacci(i));
        endl();
    }while (i)
    
    func();
    endl();
    printf("QuickSort, please 20 numbers : ");
    endl();
    for (i = 0; i < top2; i = i + 1)
        {
            scanf(x);
            list[i] = x;
        }
    
    printf("before : ");
    for (i = 0; i < top2; i = i + 1)
        printf(" ", list[i]);
    endl();
    sort(0, top2-1);
    printf("after : ");
    for (i = top2-1; i >= 0; i = i - 1)
        printf(" ", list[i]);
    return ;
}