#include <stdio.h>
#include <string.h>

#define TAG 0
#define VALUE 1

void removeTags();

int main() {
    removeTags();
    return 0;
}

/**
 * Removes tags and displays values
 */
void removeTags(){

    int mode = TAG;
    int bufferLength = 255;
    char buffer[bufferLength];

    // Read line by line
    while(fgets(buffer, bufferLength, stdin))
    {
        mode = TAG;
        for(int i = 0; i < (int) strlen(buffer); i++) {
            char c = buffer[i];
            switch (mode) {
                case TAG:
                    // Switch to value when encountering an = sign
                    if (c == '=') {
                        mode = VALUE;
                    }
                    break;
                    // Switch to tag when encountering a ';' or '\t' sign
                case VALUE:
                    if (c == ';' || c == '\t') {
                        mode = TAG;
                    }
                    putchar(c);
                    break;
            }
        }
    }
}

