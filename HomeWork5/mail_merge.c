#include	<stdio.h>
#include <stdlib.h>
#include	"fl.h"
#include	"ws13.h"

/**
 * Finite state machine stages
 */
#define PLACE_HOLDER 5
#define TEXT 6
#define EXIT 7

/**
 * Function declarations
 */
int process_text(int, int);
int process_place_holder(symtab_t * , int, int, char[], int *, int *);

/**
 * Driver function for merging mail. Delegates to FSM functions
 * @param tp , @param fp
 */
void mailmerge(symtab_t * tp, FILE * fp)
{

    int c, mode = TEXT, field_count = 0, is_env = 0;
    char field_holder[MAXFLD]; // Store field_name placeholder

    rewind(fp);

    while((c = fgetc(fp)) != EOF)
    {
        switch(mode)
        {
            case TEXT:
                mode = process_text(c, mode);
                if(mode == EXIT) break; // Exit reaching EOF
            break;
            case PLACE_HOLDER: // Read field place holder
                mode = process_place_holder(tp, c, mode, field_holder, &field_count, &is_env);
            break;
        }
    }
}


/**
 * Prints text
 * Changes mode to PLACE_HOLDER when encountering '%'
 * @param c
 * @param mode
 * @return mode
 */
int process_text(int c, int mode)
{
    if(c == '%')
        mode = PLACE_HOLDER; // Beginning of place holder
    else if(c == EOF)
        return EXIT; // End reading
    else
        putchar(c);

    return mode;
}

/**
 * Processes place holder by looking up the value when getting to closing tag
 * @param tp, @param c, @param mode, @param field_holder, @param field_count
 * @return mode
 */
int process_place_holder(symtab_t * tp,
                         int c, int mode, char field_holder[], int * field_count, int * is_env)
{
    if(c == '%') // End of placeholder
    {
        if(*field_count > 0)
        {
            field_holder[(*field_count)] = '\0';
            char * value;
            value = *is_env ==  1 ? getenv(field_holder) : lookup(tp, field_holder);
            printf("%s", value == NULL ? "" : value); // Print value
            *field_count = 0; // Reset field holder
            *field_holder = '\0';
        }
        else { // User may want to print '%' if the string in between is null
            putchar(c);
        }
        mode = TEXT; // Change to text state
    }
    else if(c == '$')
        *is_env = 1; // Read from environment
    else if(c == EOF) // Placeholder must be closed
        fatal("Need to close field place holder", "");
    else
    {
        if(*field_count < MAXFLD - 1) field_holder[(*field_count)++] = c; // Store the placeholder
    }

    return mode;
}