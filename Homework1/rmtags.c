#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAG 0
#define VALUE 1

int main(int argc,char* argv[]) {

    if(argc == 0){
        printf("Please enter a filename as an argument");
        exit(1);
    }

    int mode = TAG;

    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];

    filePointer = fopen("D:\\sample_sched.txt", "r"); // TODO - don't hardcode this

    // TODO - write comments, check how it works in reverse order
    // TODO - permission denied for dir create and where to create it, how to copy to server
    while(fgets(buffer, bufferLength, filePointer))
    {

        mode = TAG;

        for(int i = 0; i < strlen(buffer); i++) {

            char c = buffer[i];

            switch (mode) {
                case TAG:
                    if (c == '=') {
                        mode = VALUE;
                    }
                    break;
                case VALUE:
                    if (c == ';') {
                        mode = TAG;
                    }
                    putchar(c);
                    break;
            }
        }
    }

    fclose(filePointer);

    return 0;
}
