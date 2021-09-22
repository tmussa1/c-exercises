#include <stdio.h>
#include <stdlib.h>

#define	MAXFIELDS	7
#define	MAXFLDLEN	40

void displayBadTimes();
int split_line( char orig[], char fields[MAXFIELDS][MAXFLDLEN], char delim);

int main() {
    displayBadTimes();
    return 0;
}

/**
 * Parses input line by line and displays rows with incorrect time range
 */
void displayBadTimes() {

    int bufferLength = 255;
    char buffer[bufferLength];

    while (fgets(buffer, bufferLength, stdin))
    {
        /* First split to get the TI column */
        char fields[MAXFIELDS][MAXFLDLEN];
        split_line(buffer, fields, ';');

        /* Second split to get the hour and minutes */
        char time_field[MAXFIELDS][MAXFLDLEN];
        split_line(fields[3], time_field, '=');

        /* Third split to get the hours and minutes separately */
        char hour_minute[MAXFIELDS][MAXFLDLEN];
        split_line(time_field[1], hour_minute, ':');

        /* A valid tim according to the requirements is 0-25 hour and 0-59 minute */
        if(atoi(hour_minute[0]) < 0
           || atoi(hour_minute[0]) > 25
           || atoi(hour_minute[1]) < 0
           || atoi(hour_minute[1]) > 59){
            printf("%s", buffer);
        }
    }
}

int split_line( char orig[], char fields[MAXFIELDS][MAXFLDLEN], char delim)
/*
 * purpose: parse a line of DELIM-separated items into an array of strings
 *    args: a line of DELIM-separted items and an array of char arrays
 *  method: loop through orig copying and copy to target array.  Change
 *          to next row at each DELIM
 * returns: number of fields found in line
 *    note: no error checking.  See what you can do to break it
 */
{
    int	src_pos,		/* position in source array	*/
    cur_fld,		/* item in fields[] array	*/
    dest_pos;		/* position in dest array	*/

    src_pos = cur_fld = dest_pos = 0;	/* shorthand		*/

    while( 1 )
    {
        /*
         * if end of record, then terminate current string
         * and advance to next row in fields[] table
         */

        if ( orig[src_pos] == delim || orig[src_pos] == '\0' )
        {
            fields[cur_fld][dest_pos] = '\0';
            if ( orig[src_pos] == '\0' )
                break;
            cur_fld++;

            if(cur_fld >= MAXFIELDS){
                break; // Check for overflow error
            }

            dest_pos = 0;
        }
        else

            /*
             * not end of record, so copy the char from the source
             * to the current char position in the current string
             */
        {
            fields[cur_fld][dest_pos] = orig[src_pos];
            dest_pos++;

            if(dest_pos >= MAXFLDLEN){
                break; // Check for overflow error
            }
        }
        src_pos++;
    }
    return cur_fld+1;
}