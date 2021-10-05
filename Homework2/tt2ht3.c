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

#define DELIMITER 4
#define COLUMN_TEXT 5

#define DELIMITER_SIZE 2
#define COLUMN_SIZE 20 // Assuming there will be a max of 20 table columns
#define ATTRIBUTE_SIZE 40 // Assuming max attribute length is 40

void format_text_table_with_metadata();
int is_blank(char buffer[]);
void process_table_text(char buffer[], char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE], char * delimiter);
char * strsep (char **stringp, const char *delim);

// Finite state machine helper functions
int process_no_process(int mode, char buffer[], char no_process_closing_tag[]);
int process_attribute(int mode, char buffer[], char attribute_opening_tag[],
                      char attribute_closing_tag[], int length,
                      int * current_attribute_index,
                      char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]);
int process_blank_space(int mode, char buffer[], char no_process_opening_tag[], char attribute_opening_tag[],
                        char delimiter_tag[], char delimiter[], int length, char opening_row_tag[],
                        char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]);
int process_text(int mode, char buffer[], char no_process_opening_tag[], char attribute_opening_tag[],
                 char delimiter_tag[], char delimiter[], int length, char opening_row_tag[],
                 char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]);

int main(){
    format_text_table_with_metadata();
    return 0;
}

/**
 * Driver function for reading delimiter separated text
 */
void format_text_table_with_metadata(){

    int bufferLength = 255;
    char buffer[bufferLength];
    int mode = BLANK_SPACE;
    char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE] = {{0}};
    int current_attribute_index = 0;
    char delimiter[DELIMITER_SIZE] = " "; // Delimiter by default blank space
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
                mode = process_no_process(mode, buffer, no_process_closing_tag);
                break;
            case ATTRIBUTE:
                mode = process_attribute(mode, buffer, attribute_opening_tag,
                                         attribute_closing_tag, length,
                                         &current_attribute_index, attributes);
                break;
            case BLANK_SPACE:
                mode = process_blank_space(mode, buffer, no_process_opening_tag, attribute_opening_tag,
                                           delimiter_tag, delimiter, length, opening_row_tag,
                                           attributes);
                break;
            case TEXT:
                mode = process_text(mode, buffer, no_process_opening_tag, attribute_opening_tag,
                                    delimiter_tag, delimiter, length, opening_row_tag,
                            attributes);
                break;
        }
    }
}

/**
 * Switches back to the neutral blank space state when encountering
 * a closing no_process tag
 * Prints to console otherwise
 * @param mode
 * @param buffer
 * @param no_process_closing_tag
 * @return
 */
int process_no_process(int mode, char buffer[], char no_process_closing_tag[]){
    if(strstr(buffer, no_process_closing_tag)){
        mode = BLANK_SPACE;
    } else {
        printf("%s", buffer);
    }
    return mode;
}

/**
 * Switches back to neutral state when encountering
 * closing attribute tag
 * Stores attribute in a variable otherwise
 * @param mode
 * @param buffer
 * @param attribute_opening_tag
 * @param attribute_closing_tag
 * @param length
 * @param current_attribute_index
 * @param attributes
 * @return
 */
int process_attribute(int mode, char buffer[], char attribute_opening_tag[],
                      char attribute_closing_tag[], int length,
                      int * current_attribute_index, char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]){
    if(strstr(buffer, attribute_closing_tag)){
        mode = BLANK_SPACE;
    } else {
        if(strstr(buffer, attribute_opening_tag)){
            // Reset the attributes array if encountering a nested attribute tag
            (*current_attribute_index) = 0;
        } else {
            // Check for overflow
            if(*current_attribute_index < COLUMN_SIZE && length < ATTRIBUTE_SIZE){
                buffer[length - 1] = '\0'; // Skip the last new line character
                strcpy(attributes[(*current_attribute_index)++], buffer);
            }
        }
    }
    return mode;
}

/**
 * Works the same way as version 2 except for saving a delimiter
 * when finding one
 * @param mode
 * @param buffer
 * @param no_process_opening_tag
 * @param attribute_opening_tag
 * @param delimiter_tag
 * @param delimiter
 * @param length
 * @param opening_row_tag
 * @param attributes
 * @return
 */
int process_blank_space(int mode, char buffer[], char no_process_opening_tag[], char attribute_opening_tag[],
                        char delimiter_tag[], char delimiter[], int length, char opening_row_tag[],
                        char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]) {
    if(strstr(buffer, no_process_opening_tag)){
        mode = NO_PROCESS;
    } else if(strstr(buffer, attribute_opening_tag)){
        mode = ATTRIBUTE;
    } else if(strstr(buffer, delimiter_tag)) {
        char * token = strtok(buffer, "=");
        token = strtok(NULL, "=");
        delimiter[0] = token[0]; // Save delimiter
        delimiter[1] = '\0';
    } else if(length > 0 && !is_blank(buffer)){
        mode = TEXT;
        printf("\t%s\n\t", opening_row_tag);
        process_table_text(buffer, attributes, delimiter);
    }
    return mode;
}

/**
 * Works the same way as version 2 except for saving a delimiter
 * @param mode
 * @param buffer
 * @param no_process_opening_tag
 * @param attribute_opening_tag
 * @param delimiter_tag
 * @param delimiter
 * @param length
 * @param opening_row_tag
 * @param attributes
 * @return
 */
int process_text(int mode, char buffer[], char no_process_opening_tag[], char attribute_opening_tag[],
                 char delimiter_tag[], char delimiter[], int length, char opening_row_tag[],
                 char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]) {
    if(strstr(buffer, no_process_opening_tag)){
        mode = NO_PROCESS;
    } else if(strstr(buffer, attribute_opening_tag)){
        mode = ATTRIBUTE;
    } else if(strstr(buffer, delimiter_tag)) {
        char * token = strtok(buffer, "=");
        token = strtok(NULL, "=");
        delimiter[0] = token[0]; // Save delimiter
        delimiter[1] = '\0';
    } else {
        if (length > 0 && !is_blank(buffer)) {
            printf("\t%s\n\t", opening_row_tag);
            process_table_text(buffer, attributes, delimiter);
        }
    }
    return mode;
}
/**
 * Processes each line by enclosing with tr and td tags
 * Appends attributes if provided
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
        if(word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0'; // Get rid of new line
        }
        printf("%s", word);
        printf("%s", closing_column_tag);
    }

    printf("\n\t%s\n", closing_row_tag);
}

/**
 * Checks if a line contains only blank space
 * @param buffer
 * @return
 */
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

