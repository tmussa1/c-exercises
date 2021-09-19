#include <stdio.h>
#include <string.h>

#define SINGLE_LINE_COMMENT 0
#define MULTI_LINE_COMMENT 1
#define CODE 2
#define SINGLE_NESTED_IN_MULTI_COMMENT 3

int main() {

    int mode = CODE;

    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];

    filePointer = fopen("D:\\myprog.c", "r");
    // TODO - don't hardcode this, take out spaces
    // TODO - move them to helper, how to pass args, how to mkdir in server and where
    // TODO - 30 lines per func

    while(fgets(buffer, bufferLength, filePointer))
    {
        for(int i = 0; i < strlen(buffer); i++) {
            switch (mode) {
                case CODE: {
                    char c1 = buffer[i], c2 = buffer[i + 1];
                    if(c1 == '/' && c2 == '*'){
                        mode = MULTI_LINE_COMMENT;
                        putchar(c1);
                    }
                    if(c1 == '/' && c2 == '/'){
                        mode = SINGLE_LINE_COMMENT;
                        putchar(c1);
                    }
                    break;
                }
                case SINGLE_LINE_COMMENT: {
                    if(i == strlen(buffer) - 1){
                        mode = CODE;
                    }
                    char c = buffer[i];
                    putchar(c);
                    break;
                }
                case MULTI_LINE_COMMENT: {
                    char c1 = buffer[i], c2 = buffer[i + 1];
                    if(c1 == '/' && c2 == '/'){
                        mode = SINGLE_NESTED_IN_MULTI_COMMENT;
                        putchar(c1);
                    }
                    else if(c1 == '*' && c2 == '/'){
                        mode = CODE;
                        putchar(c1);
                        putchar(c2);
                        putchar('\n');
                    }
                    else {
                        char c = buffer[i];
                        putchar(c);
                    }
                    break;
                }
                case SINGLE_NESTED_IN_MULTI_COMMENT: {
                    if(i == strlen(buffer) - 1){
                        mode = MULTI_LINE_COMMENT;
                    }
                    char c = buffer[i];
                    putchar(c);
                    break;
                }
            }
        }
    }

    fclose(filePointer);

    return 0;
}