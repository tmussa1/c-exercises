#include	<stdio.h>
#include    <ctype.h>
#include	"fl.h"
#include	"ws13.h"

/**
 *  This files reads records and inserts field/values
 *  to word store after processing. It accomplishes this
 *  by using helper methods for each state of the finite
 *  state machine
 */

/**
 * Status values
 */
#define	YES	1
#define	NO	0

/**
 * Record mode values (Finite State Machine states)
 */
#define WHITE_SPACE 2
#define FIELD 3
#define VALUE 4

#define REDELIM '\n' // TODO - get this from env
#define FDELIM ';' // TODO - get this from env

/**
* Function declarations
*/
int process_space(int c, int , char [], int);
int process_field(int, int, char [], int);
int process_value(int, int, char [], int, char[], symtab_t *);
int check_bounds(int, int);

/**
 * Driver function for reading records. Delegates to helper functions
 * defined above in each stage of the finite state machine
 * Returns YES in successful processing of records. Bubbles up fatal exception
 * @param tp, @param fp
 * @return YES or NO, throws exception for processing error
 */
int	get_record(symtab_t * tp, FILE *fp)
{
    int c, mode = WHITE_SPACE, field_count = 0, value_count = 0;
    char field[MAXFLD], value[MAXVAL]; // Stores field and value

    while((c = fgetc(fp)) != EOF){
        switch(mode){ // Starts on white space state
            case WHITE_SPACE:
                mode = process_space(c, mode, field, field_count);
                if(mode == YES) return YES; // Reached EOF or record delimiter
            break;
            case FIELD: // Process fields
                mode = process_field(c, mode, field, field_count);
            break;
            case VALUE:
                mode = process_value(c, mode, value, value_count, field, tp);
                if(mode == YES) { // TODO - ask Bruce about freeing up memory
                    value_count = field_count = 0; // Reset field and value counts
                    field[field_count] = value[value_count] = '\0'; // Clear string
                    return YES;
                }
            break;
        }
    }
    return YES;
}

/**
 * Ignores leading white space
 * Throws error if encountering '=' sign before a field is read
 * Changes to field state if it encounters a non-space character
 * @param c
 * @param mode
 * @param field
 * @param field_count
 * @return mode or status - YES, throws exception
 */
int process_space(int c, int mode, char field[], int field_count)
{
    if(c == '=')
        fatal("Value found without field name", "");
    else if(c == EOF || c == REDELIM)
        return YES; // We are done and can exit
    else if(!isspace(c))
    {
        field[field_count++] = c; // Store character
        mode = FIELD; // Change to field state
    }
    return mode;
}

/**
 * Switches state to value if it encounters '=' sign
 * Throws exception when encountering field or record delimiter
 * because fields without a placeholder for value are not allowed
 * Reads the character into field array otherwise
 * @param c
 * @param mode
 * @param field
 * @param field_count
 * @return mode
 */
int process_field(int c, int mode, char field[], int field_count)
{
    if(c == '=')
    {
        if(check_bounds(MAXFLD, field_count))
            field[field_count] = '\0'; // Terminate array
        mode = VALUE;
    }
    else if(c == FDELIM || c == REDELIM)
        fatal("Field found without placeholder for value", "");
    else
    {
        if(check_bounds(MAXFLD, field_count)) // Check bounds
            field[field_count++] = c;
    }

    return mode;
}

/**
 * Processes values. Inserts values after reaching record or field delimiter
 * @param c, @param mode,
 * @param value, @param value_count, @param field , @param field_count
 * @return status or mode
 */
int process_value(int c, int mode,
                  char value[], int value_count, char field[], symtab_t * tp)
{
    if(c == REDELIM || c == FDELIM) {
        value[value_count] = '\0'; // Terminate array
        if (in_table(tp, field) == YES)
        {
            if (update(tp, field, value) == NO)
                fatal("Can not update record", value);
        }
        else
        {
            if (insert(tp, field, value) == NO)
                fatal("Can not insert record", value);
        }
        return YES; // Record was successfully inserted
    }
    else
    {
        if(check_bounds(MAXFLD, value_count))
            value[value_count++] = c; // Put the character in correct spot
    }

    return mode; // Return mode and continue reading
}

/**
 * Checks if an array is in bounds
 * @param max
 * @param current_count
 * @return YES or NO
 */
int check_bounds(int max, int current_count)
{
    return current_count < max - 1 ? YES : NO; // Account for null terminator
}