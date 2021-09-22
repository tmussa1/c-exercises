#include <stdio.h>
#include <string.h>

#define SINGLE_LINE_COMMENT 0
#define MULTI_LINE_COMMENT 1
#define CODE 2
#define SINGLE_NESTED_IN_MULTI_COMMENT 3

void extractComments();
void readMultiLineComment(char buffer[], int i, int * mode);
void readSingleLineComment(char buffer[], int i, int * mode);
void readSingleLineNestedInMultiLineComment(char buffer[], int i, int * mode);
void skipCode(char buffer[], int i, int * mode);

int main() {
    extractComments();
    return 0;
}

/**
 * Extracts comments from a program
 */
void extractComments() {
    int mode = CODE;
    int bufferLength = 255;
    char buffer[bufferLength];

    while(fgets(buffer, bufferLength, stdin))
    {
        for(int i = 0; i < (int) strlen(buffer); i++) {
            switch (mode) {
                case CODE: {
                    skipCode(buffer, i, &mode); // Skip code
                    break;
                }
                case SINGLE_LINE_COMMENT: {
                    readSingleLineComment(buffer, i, &mode); // Read single line comments
                    break;
                }
                case MULTI_LINE_COMMENT: {
                    readMultiLineComment(buffer, i, &mode); // Read multiline comments
                    break;
                }
                case SINGLE_NESTED_IN_MULTI_COMMENT: {
                    readSingleLineNestedInMultiLineComment(buffer, i, &mode);
                    // Read single line comments nested in multiline
                    break;
                }
            }
        }
    }
}

/**
 * Helper method to read mutliline comments
 * @param buffer
 * @param i
 * @param mode
 */
void readMultiLineComment(char buffer[], int i, int * mode){
    char c1 = buffer[i], c2 = buffer[i + 1];
    if(c1 == '/' && c2 == '/'){
        // Keep reading when encoutering nested comment
        *mode = SINGLE_NESTED_IN_MULTI_COMMENT;
        putchar(c1);
    }
    else if(c1 == '*' && c2 == '/'){
        // End reading comment
        *mode = CODE;
        putchar(c1);
        putchar(c2);
        putchar('\n');
    }
    else {
        // Output characters if neither
        char c = buffer[i];
        putchar(c);
    }
}

void skipCode(char buffer[], int i, int * mode){
    char c1 = buffer[i], c2 = buffer[i + 1];
    if(c1 == '/' && c2 == '*'){
        *mode = MULTI_LINE_COMMENT;
        putchar(c1);
    }
    if(c1 == '/' && c2 == '/'){
        *mode = SINGLE_LINE_COMMENT;
        putchar(c1);
    }
}

void readSingleLineComment(char buffer[], int i, int * mode) {
    if(i == (int) strlen(buffer) - 1){
        // End of single line comment
        *mode = CODE;
    }
    char c = buffer[i];
    putchar(c);
}

void readSingleLineNestedInMultiLineComment(char buffer[], int i, int * mode) {
    if(i == (int) strlen(buffer) - 1){
        // End of nested comment in a multiline
        *mode = MULTI_LINE_COMMENT;
    }
    char c = buffer[i];
    putchar(c);
}