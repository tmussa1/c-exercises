#include <stdio.h>
#include <string.h>

#define BLANK_SPACE 0
#define NO_PROCESS 1
#define ATTRIBUTE 2
#define TEXT 3

#define COLUMN_SIZE 20 // Assuming there will be a max of 20 table columns
#define ATTRIBUTE_SIZE 40 // Assuming max attribute length is 40

void format_text_table_with_metadata();

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

    while (fgets(buffer, bufferLength, stdin)) {
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
                    }
                    strcpy(attributes[current_attribute_index++], buffer);
                }
            break;
            case BLANK_SPACE:
                if(strstr(buffer, no_process_opening_tag)){
                    mode = NO_PROCESS;
                } else if(strstr(buffer, attribute_opening_tag)){
                    mode = ATTRIBUTE;
                } else if(strlen(buffer) > 0){
                    mode = TEXT;
                }
            break;
        }
    }
}