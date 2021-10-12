#include <stdio.h>

int main()
{
    char names[4][10] = { "anna", "ben", "carol", "david" };
    char *p[4] = { names[3], names[2], names[1], names[0] };
    int i;
    for ( i = 0 ; i < 4 ; i++ ){
        p[i] += i;
        printf("%s, p is in %p. &p[%d]=%p\n", p[i], p[i], i, &p[i]);
    }
    for ( int j = 0 ; j < 4 ; j++ ){
        printf("%s, names is in %p, names[%d]=%p\n", names[j], names[j], j, &names[j]);
    }
}
