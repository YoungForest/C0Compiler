int fibonacci(int n)
{
    if(n >= 0)
        if(n <= 1)
            return (1);
        else
            return (fibonacci(n-1) + fibonacci(n-2));
    else
        return (0)
}
void endl()
{
    char c;
    c = 10;
    printf(c)
}
void main()
{
    int x;
    do{
    printf("Input a number, get its fibonacci: ");
    scanf(x1);
    printf("Its fibonacci: ", fibonacci(x));
    endl();
    }while (x >= );
}