#include <stdio.h>

/**
 * Exercise to understand pointers
*/

char t[3] = "hi";
int main()
{
    char m[20] = "arrays != pointers";
    int *x;
    char *y, *z;
    int **w, a;
    int b[] = { 8, 6, 4, 2 };
    x=&b[0];
    y=m+5;
    z=(char *) &a;
    *z = '3';
    a=74;
    w=&x;
    *x = x[2] + --a;

    printf("t=%s and &t=%p\n", t, &t);
    printf("m=%s and &m=%p\n", m, &m);
    printf("x=%p *x=%d &x=%p\n", x, *x, &x);
    printf("y=%p *y=%c &y=%p\n", y, *y, &y);
    printf("z=%p *z=%d &z=%p\n", z, *z, &z);
    printf("w=%p *w=%p **w=%d &w=%p\n", w, *w, **w, &w);
    printf("a=%d &a=%p\n", a, &a);
    printf("b=%p *b=%d &b=%p\n", b, *b, &b);
    return 0;
}

