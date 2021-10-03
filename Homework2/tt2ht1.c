#include <stdio.h>
#include <string.h>

#define NEW_LINE 0
#define DELIMITER 1
#define TEXT 2

void formatTextTableOutput(char opening_table_tag[], char closing_table_tag[],
                           char opening_row_tag[], char opening_column_tag[],
                           char closing_column_tag[], char closing_row_tag[]);
int process_text(char c, char closing_column_tag[6], char closing_row_tag[6], int mode);
int process_delimiter(char c, char opening_column_tag[5], int mode);
int process_new_line(char c, char tag[52], char tag1[5], char tag2[5], int mode, int containsText);

int main(){

    char opening_table_tag[] = "\n<table border='1' cellpadding='3' cellspacing='1'>";
    char closing_table_tag[] = "</table>";
    char opening_row_tag[] = "<tr>";
    char opening_column_tag[] = "<td>";
    char closing_column_tag[] = "</td>";
    char closing_row_tag[] = "</tr>";

    formatTextTableOutput(opening_table_tag, closing_table_tag,
                          opening_row_tag, opening_column_tag,
                          closing_column_tag, closing_row_tag);
    return 0;
}

void formatTextTableOutput(char opening_table_tag[], char closing_table_tag[],
                           char opening_row_tag[], char opening_column_tag[],
                           char closing_column_tag[], char closing_row_tag[]) {

    int bufferLength = 255;
    char buffer[bufferLength];
    int containsText = 0;
    int mode;

    while (fgets(buffer, bufferLength, stdin)) {
        size_t length = strlen(buffer);
        mode = NEW_LINE;
        for (size_t i = 0; i < length; i++) {
            char c = buffer[i];
            switch (mode) {
                case TEXT:
                    containsText = 1;
                    mode = process_text(c, closing_column_tag, closing_row_tag, mode);
                break;
                case DELIMITER:
                    mode = process_delimiter(c, opening_column_tag, mode);
                break;
                case NEW_LINE:
                    mode = process_new_line(c, opening_table_tag, opening_row_tag, opening_column_tag, mode, containsText);
                break;
            }
        }
    }

    if(containsText == 1){
        printf("%s\n", closing_table_tag);
    }
}


int process_text(char c, char closing_column_tag[], char closing_row_tag[], int mode) {
    if (c == ' ' || c == '\t') {
        printf("%s\t", closing_column_tag);
        mode = DELIMITER;
    } else if (c == '\n') {
        printf("%s", closing_column_tag);
        printf("\n\t%s\n", closing_row_tag);
        mode = NEW_LINE;
    } else {
        putchar(c);
    }
    return mode;
}

int process_delimiter(char c, char opening_column_tag[5], int mode) {
    if (c != ' ' && c != '\t') {
        printf("%s", opening_column_tag);
        putchar(c);
        mode = TEXT;
    }
    return mode;
}

int process_new_line(char c, char opening_table_tag[], char opening_row_tag[], char opening_column_tag[], int mode, int containsText) {
    if(c != ' ' && c != '\t' && c != '\n'){
        if(containsText == 0){
            printf("%s\n", opening_table_tag);
        }
        printf("\t%s\n", opening_row_tag);
        printf("\t\t%s", opening_column_tag);
        putchar(c);
        mode = TEXT;
    }
    return mode;
}
