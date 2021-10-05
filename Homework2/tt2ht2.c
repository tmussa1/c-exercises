#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * These four associated with the outer finite state machine
 */
#define BLANK_SPACE 0
#define NO_PROCESS 1
#define ATTRIBUTE 2
#define TEXT 3

/**
 * These two associated with the inner finite state machine
 */
#define DELIMITER 4
#define COLUMN_TEXT 5

#define COLUMN_SIZE 20 // Assuming there will be a max of 20 table columns
#define ATTRIBUTE_SIZE 40 // Assuming max attribute length is 40

void format_text_table_with_metadata();
int is_blank(char buffer[]);

// Inner state machine functions
void process_table_text(char buffer[], char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]);
int process_delimiter(int mode, char c, char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE],
                      int * current_attribute_index, char opening_column_tag[],
                      char closing_angle_bracket[]);
int process_column_text(int mode, char c, char closing_column_tag[]);

//Outer state machine functions
int process_no_process(int mode, char buffer[], char no_process_closing_tag[]);
int process_attribute(int mode, char buffer[], char attribute_opening_tag[],
                      char attribute_closing_tag[], int length,
                      int * current_attribute_index,
                      char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]);
int process_blank_space(int mode, char buffer[], char no_process_opening_tag[],
                        char attribute_opening_tag[], int length, char opening_row_tag[],
                        char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]);
int process_text(int mode, char buffer[], int length, char no_process_opening_tag[],
                 char attribute_opening_tag[], char opening_row_tag[],
                 char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]);

int main(){
    format_text_table_with_metadata();
    return 0;
}

/**
 * Driver method for the outer finite state machine
 * It can be in one of these states - NO_PROCESS, ATTRIBUTE, BLANK_SPACE, TEXT
 */
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
               mode = process_no_process(mode, buffer, no_process_closing_tag);
            break;
            case ATTRIBUTE:
                mode = process_attribute(mode, buffer, attribute_opening_tag,
                                         attribute_closing_tag, length,
                                         &current_attribute_index, attributes);
            break;
            case BLANK_SPACE:
                mode = process_blank_space(mode, buffer, no_process_opening_tag,
                                           attribute_opening_tag, length, opening_row_tag,
                                           attributes);
            break;
            case TEXT:
                mode = process_text(mode, buffer, length, no_process_opening_tag,
                                    attribute_opening_tag, opening_row_tag, attributes);
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
            *current_attribute_index = 0;
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
 * Switches to NO_PROCESS or ATTRIBUTE if encountering a closing tag of those
 * Or processes the row and prints text inside tr and td tags
 * @param mode
 * @param buffer
 * @param no_process_opening_tag
 * @param attribute_opening_tag
 * @param length
 * @param opening_row_tag
 * @param attributes
 * @return
 */
int process_blank_space(int mode, char buffer[], char no_process_opening_tag[],
                        char attribute_opening_tag[], int length, char opening_row_tag[],
                        char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]){
    if(strstr(buffer, no_process_opening_tag)){
        mode = NO_PROCESS;
    } else if(strstr(buffer, attribute_opening_tag)){
        mode = ATTRIBUTE;
    } else if(length > 0){
        mode = TEXT;
        printf("\t%s\n\t", opening_row_tag);
        process_table_text(buffer, attributes);
    }
    return mode;
}

/**
 * Switches to NO_PROCESS or ATTRIBUTE if encountering an opening tag of those
 * Or processes the row and prints text inside tr and td tags
 * @param mode
 * @param buffer
 * @param length
 * @param no_process_opening_tag
 * @param attribute_opening_tag
 * @param opening_row_tag
 * @param attributes
 * @return
 */
int process_text(int mode, char buffer[], int length, char no_process_opening_tag[],
                 char attribute_opening_tag[], char opening_row_tag[], char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]) {
    if(strstr(buffer, no_process_opening_tag)){
        mode = NO_PROCESS;
    } else if(strstr(buffer, attribute_opening_tag)){
        mode = ATTRIBUTE;
    } else {
        if(length > 0 && !is_blank(buffer)){
            printf("\t%s\n\t", opening_row_tag);
            process_table_text(buffer, attributes);
        }
    }
    return mode;
}

/**
 * Processes table text line by line
 * Uses inner finite state machine to switch between text and delimiter
 * @param buffer
 * @param attributes
 */
void process_table_text(char buffer[], char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE]) {

    int mode = DELIMITER;
    int length = strlen(buffer);
    char opening_column_tag[] = "<td";
    char closing_angle_bracket[] = ">";
    char closing_column_tag[] = "</td>";
    char closing_row_tag[] = "</tr>";
    int current_attribute_index;

    // Skip the last new line character
    for(int i = 0; i < length - 1; i++){
        char c = buffer[i];
        switch(mode){
            case DELIMITER:
                mode = process_delimiter(mode, c, attributes, &current_attribute_index,
                                         opening_column_tag, closing_angle_bracket);
            break;
            case COLUMN_TEXT:
                mode = process_column_text(mode, c, closing_column_tag);
            break;
        }
    }
    printf("%s", closing_column_tag);
    printf("\n\t%s\n", closing_row_tag);
}

/**
 * Processes delimiter
 * Checks for a non-blank character
 * Prints attributes if exists and puts in td tag, then prints the character
 * @param mode
 * @param c
 * @param attributes
 * @param current_attribute_index
 * @param opening_column_tag
 * @param closing_angle_bracket
 * @return
 */
int process_delimiter(int mode, char c, char attributes[COLUMN_SIZE][ATTRIBUTE_SIZE],
                      int * current_attribute_index, char opening_column_tag[],
                      char closing_angle_bracket[]){
    if(c != ' ' && c != '\t' && c != '\n'){
        mode = COLUMN_TEXT;
        char attribute[ATTRIBUTE_SIZE];

        if((*current_attribute_index) < ATTRIBUTE_SIZE){
            strcpy(attribute, attributes[(*current_attribute_index)++]);
        }
        if(is_blank(attribute)){
            printf("%s%s", opening_column_tag, closing_angle_bracket);
        } else {
            printf("%s %s%s", opening_column_tag, attribute, closing_angle_bracket);
        }

        putchar(c);
    }
    return mode;
}

/**
 * Switches mode to delimiter when encountering a blank character
 * and prints closing td tag
 * Prints charcter otherwise
 * @param mode
 * @param c
 * @param closing_column_tag
 * @return
 */
int process_column_text(int mode, char c, char closing_column_tag[]){

    if(c == ' ' || c == '\t'){
        mode = DELIMITER;
        printf("%s", closing_column_tag);
    } else {
        putchar(c);
    }

    return mode;
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
