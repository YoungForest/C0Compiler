int power(int a, int b) {
    if(b > 0) {
        return (a * power(a, b-1));
    }
    else if(b == 0){return (1);}
    else{return(1);}
}
void endl()
{
    char c;
    c = 10;
    printf(c);
}
void main() {
    int i,a,b,x;
    i = 3;
    do {
        printf("Input 2 Integer:");
        scanf(a,b);
        x=power(a,b);
        printf(x);
        endl();
        i = i - 1;
    } while(i)
}