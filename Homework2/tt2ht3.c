#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

#define DELIMITER_SIZE 2
#define COLUMN_SIZE 20 // Assuming there will be a max of 20 table columns
#define ATTRIBUTE_SIZE 40 // Assuming max attribute length is 40

void format_text_table_with_metadata();
int is_blank(char buffer[]);
void process_table_text(char buffer[], char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE], char * delimiter);
char * strsep (char **stringp, const char *delim);

int main(){
    format_text_table_with_metadata();
    return 0;
}

void format_text_table_with_metadata(){

    int bufferLength = 255;
    char buffer[bufferLength];
    int mode = BLANK_SPACE;
    char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE] = {{0}};
    int current_attribute_index = 0;
    char delimiter[DELIMITER_SIZE] = " ";
    char delimiter_tag[]= "<delim";
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
                            buffer[length - 1] = '\0'; // Skip the last new line character
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
                } else if(strstr(buffer, delimiter_tag)) {
                    char * token = strtok(buffer, "=");
                    token = strtok(NULL, "=");
                    delimiter[0] = token[0];
                    delimiter[1] = '\0';
                } else if(length > 0 && !is_blank(buffer)){
                    mode = TEXT;
                    printf("\t%s\n\t", opening_row_tag);
                    process_table_text(buffer, attributes, delimiter);
                }
                break;
            case TEXT:
                if(strstr(buffer, no_process_opening_tag)){
                    mode = NO_PROCESS;
                } else if(strstr(buffer, attribute_opening_tag)){
                    mode = ATTRIBUTE;
                } else if(strstr(buffer, delimiter_tag)) {
                    char * token = strtok(buffer, "=");
                    token = strtok(NULL, "=");
                    delimiter[0] = token[0];
                    delimiter[1] = '\0';
                } else {
                    if (length > 0 && !is_blank(buffer)) {
                        printf("\t%s\n\t", opening_row_tag);
                        process_table_text(buffer, attributes, delimiter);
                    }
                }
                break;
        }
    }
}

/**
 *
 * @param buffer
 * @param attributes
 * @param delimiter
 */
void process_table_text(char buffer[], char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE], char * delimiter) {

    char opening_column_tag[] = "<td";
    char closing_angle_bracket[] = ">";
    char closing_column_tag[] = "</td>";
    char closing_row_tag[] = "</tr>";
    int current_attribute_index = 0;
    char * word;

    while((word = strsep(&buffer, delimiter)) != NULL){
        printf("%s", opening_column_tag);
        char attribute[ATTRIBUTE_SIZE];
        if(attributes != NULL && attributes[current_attribute_index] != 0){
            strcpy(attribute, attributes[current_attribute_index++]);
            if(!is_blank(attribute)){
                printf(" %s", attribute);
            }
        }
        printf("%s",closing_angle_bracket);
        word[strlen(word) - 1] = '\0';
        printf("%s", word);
        printf("%s", closing_column_tag);
    }

    printf("\n\t%s\n", closing_row_tag);
}

int is_blank(char buffer[]){
    size_t length = strlen(buffer);
    size_t i = 0;

    while(i < length){
        if(!isspace(buffer[i])){
            return 0;
        }
        i++;
    }
    return 1;
}

/**
 * This source code is taken from the GNU library because I couldn't get the library to work
 * @param stringp
 * @param delim
 * @return
 */
char * strsep (char **stringp, const char *delim)
{
    char *begin, *end;
    begin = *stringp;
    if (begin == NULL)
        return NULL;
    /* Find the end of the token.  */
    end = begin + strcspn (begin, delim);
    if (*end)
    {
        /* Terminate the token and set *STRINGP past NUL character.  */
        *end++ = '\0';
        *stringp = end;
    }
    else
        /* No more delimiters; this is the last token.  */
        *stringp = NULL;
    return begin;
}

