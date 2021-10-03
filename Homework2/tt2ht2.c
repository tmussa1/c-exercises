#include <stdio.h>
#include <string.h>

/**
 * This four associated with the outer finite state machine
 */
#define BLANK_SPACE 0
#define NO_PROCESS 1
#define ATTRIBUTE 2
#define TEXT 3

/**
 * This two associated with the outer finite state machine
 */
#define DELIMITER 4
#define COLUMN_TEXT 5

#define COLUMN_SIZE 20 // Assuming there will be a max of 20 table columns
#define ATTRIBUTE_SIZE 40 // Assuming max attribute length is 40

void format_text_table_with_metadata();

void process_table_text(char buffer[], char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]);

int main(){
    format_text_table_with_metadata();
    return 0;
}

void format_text_table_with_metadata(){

    int bufferLength = 255;
    char buffer[bufferLength];
    int mode = BLANK_SPACE;
    char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE];
    int current_attribute_index = 0;

    char attribute_opening_tag[] = "<attributes>";
    char attribute_closing_tag[] = "</attributes>";
    char no_process_opening_tag[] = "<noprocess>";
    char no_process_closing_tag[] = "</noprocess>";
    char opening_row_tag[] = "<tr>";

    while (fgets(buffer, bufferLength, stdin)) {
        size_t length = strlen(buffer);
        switch(mode){
            case NO_PROCESS:
                if(strstr(buffer, no_process_closing_tag)){
                    mode = BLANK_SPACE;
                } else {
                    printf("%s", buffer);
                }
            break;
            case ATTRIBUTE:
                if(strstr(buffer, attribute_closing_tag)){
                    mode = BLANK_SPACE;
                } else {
                    if(strstr(buffer, attribute_opening_tag)){
                        current_attribute_index = 0;
                    } else {
                        if(current_attribute_index < COLUMN_SIZE && length < ATTRIBUTE_SIZE){
                            buffer[length - 2] = '\0'; // TODO - change to -1
                            strcpy(attributes[current_attribute_index++], buffer);
                        }
                    }
                }
            break;
            case BLANK_SPACE:
                if(strstr(buffer, no_process_opening_tag)){
                    mode = NO_PROCESS;
                } else if(strstr(buffer, attribute_opening_tag)){
                    mode = ATTRIBUTE;
                } else if(length > 0){
                    mode = TEXT;
                    printf("\t%s\n\t", opening_row_tag);
                    process_table_text(buffer, attributes);
                }
            break;
            case TEXT:
                if(strstr(buffer, no_process_opening_tag)){
                    mode = NO_PROCESS;
                } else if(strstr(buffer, attribute_opening_tag)){
                    mode = ATTRIBUTE;
                } else {
                    if(length > 0){
                        printf("\t%s\n\t", opening_row_tag);
                        process_table_text(buffer, attributes);
                    }
                }
            break;
        }
    }
}

void process_table_text(char buffer[], char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]) {

    int mode = DELIMITER;
    int length = strlen(buffer);
    char opening_column_tag[] = "<td";
    char closing_angle_bracket[] = ">";
    char closing_column_tag[] = "</td>";
    char closing_row_tag[] = "</tr>";
    int current_attribute_index = 0;

    // TODO - should be length - 1
    for(int i = 0; i < length - 2; i++){
        char c = buffer[i];
        switch(mode){
            case DELIMITER:
                if(c != ' ' && c != '\t' && c != '\n'){
                    mode = COLUMN_TEXT;
                    char attribute[ATTRIBUTE_SIZE];
                    strcpy(attribute, attributes[current_attribute_index++]);
                    // TODO - check overflow error
                    printf("%s %s%s", opening_column_tag, attribute, closing_angle_bracket);
                    putchar(c);
                }
            break;
            case COLUMN_TEXT:
                if(c == ' ' || c == '\t'){
                    mode = DELIMITER;
                    printf("%s", closing_column_tag);
                } else {
                    putchar(c);
                }
            break;
        }
    }

    printf("%s", closing_column_tag);
    printf("\n\t%s\n", closing_row_tag);
}
