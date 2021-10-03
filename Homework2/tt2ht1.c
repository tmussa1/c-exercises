#include <stdio.h>
#include <string.h>

#define NEW_LINE 0
#define DELIMITER 1
#define TEXT 2

void formatTextTableOutput();

int main(){
    formatTextTableOutput();
    return 0;
}

void formatTextTableOutput() {

    int bufferLength = 255;
    char buffer[bufferLength];
    int lines = 0;
    int mode;

    char opening_table_tag[] = "\n<table border='1' cellpadding='3' cellspacing='1'>";
    char closing_table_tag[] = "</table>";
    char opening_row_tag[] = "<tr>";
    char opening_column_tag[] = "<td>";
    char closing_column_tag[] = "</td>";
    char closing_row_tag[] = "</tr>";

    while (fgets(buffer, bufferLength, stdin)) {
        size_t length = strlen(buffer);

        mode = NEW_LINE;

        for (size_t i = 0; i < length; i++) {

            char c = buffer[i];

            switch (mode) {
                case TEXT:
                    if (c == ' ' || c == '\t') {
                        printf("%s\t", closing_column_tag);
                        mode = DELIMITER;
                    } else if (c == '\n') {
                        printf("%s", closing_column_tag);
                        printf("\t%s\n", closing_row_tag);
                        mode = NEW_LINE;
                    } else {
                        putchar(c);
                    }
                break;
                case DELIMITER:
                    if (c != ' ' && c != '\t') {
                        printf("%s", opening_column_tag);
                        putchar(c);
                        mode = TEXT;
                    }
                break;
                case NEW_LINE:
                    if(c != ' ' && c != '\t' && c != '\n'){
                        if(lines == 0){
                            printf("%s\n", opening_table_tag);
                        }
                        printf("\t%s\t", opening_row_tag);
                        printf("%s", opening_column_tag);
                        putchar(c);
                        mode = TEXT;
                    }
                break;
            }
        }
        lines++;
    }

    if(lines > 0){
        printf("%s\n", closing_table_tag);
        return;
    }
}