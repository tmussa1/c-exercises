#include <stdio.h>
#include <string.h>
/* arrays are not pointer variables */
int main()
{
    char month[20] = "October";
    char *season = "fall";
    printf("%s is a %s month, month=%p season=%p\n", month, season, month, season);
    strcpy(month, "February"); // use strcpy
    season = "winter";
    printf("%s is a %s month, month=%p season=%p\n", month, season, month, season);
    strcpy(month, "April");
    season = "spring";
    printf("%s is a %s month, month=%p season=%p\n", month, season, month, season);
    return 0;
}
