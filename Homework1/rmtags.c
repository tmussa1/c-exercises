#include <stdio.h>

#define TAG 0
#define VALUE 1

int main() {

    int c;
    int mode = TAG;

    while((c = getchar()) != EOF)
    {
        switch(mode)
        {
            case TAG:
                if(c == '='){
                    mode = VALUE;
                }
            break;
            case VALUE:
                if(c == ';'){
                    mode = TAG;
                }
                putchar(c);
            break;
        }
    }
    return 0;
}
