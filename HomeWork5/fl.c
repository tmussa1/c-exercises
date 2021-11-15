#include	<stdio.h>
#include	<stdlib.h>
#include	"fl.h"

/*
 *	formletter program version 1.0
 *
 *	usage: fl format < datafile
 *
 *	data comes from stdin, output goes to stdout
 */

static char	*myname ;		/* used by fatal() */

/**
 * Function declarations
 */
int count_files(int, char *[]);
void process_arguments(int, char * [], char *, char *);
void set_delimiters(char *[], int, char *, char *);
FILE * open_file_set_delimiters(int, char *[], char *, char *);
void process_multiple_files(int, char *[], char *, char *);

int main(int ac, char *av[])
{
	myname = *av;
    char field_delimiter = ';', record_delimiter = '\n';

	/*
	 * 	check that there is at least one arg: the format file
	 */
	if ( ac == 1 )
		fatal("usage: fl format [datafile..]","");

    // Process arguments
    process_arguments(ac, av, &field_delimiter, &record_delimiter);

	return 0;
}

/**
 * Processes command line arguments
 * Reads data from stdin if only one file is provided
 * @param fpfmt , @param ac , @param av , @param field_delimiter , @param record_delimiter
 */
void process_arguments(int ac, char *av[],
                       char * field_delimiter, char * record_delimiter)
{
    if(count_files(ac, av) == 1) // Read from stdin if only format is passed
    {
        FILE * fp = open_file_set_delimiters(ac, av, field_delimiter, record_delimiter);
        process(fp, stdin, *field_delimiter, *record_delimiter);
    }
    else { // Process multiple files
        process_multiple_files(ac, av, field_delimiter, record_delimiter);
    }
}

/**
 * Sets delimiters and sequentially reads files
 * Supports reading multiple files
 * @param ac , @param av , @param field_delimiter , @param record_delimiter
 */
void process_multiple_files(int ac, char *av[],
                            char * field_delimiter, char * record_delimiter)
{
    FILE *fpfmt = NULL;

    for(int i = 1; i < ac; i++){
        if(av[i][0] == '-'){ // Set delimiters
            set_delimiters(av, i, field_delimiter, record_delimiter);
        } else {

            if (fpfmt == NULL){ // Open format file when first finding it
                if((fpfmt = fopen(av[i], "r") ) == NULL )
                    fatal("Can't open data file", "");
            }
            else {
                FILE * data;
                // Read and process data files
                if ( (data = fopen(av[i], "r") ) == NULL )
                    fatal("Can't open data file", "");
                else { // Process data with current delimiter
                    process(fpfmt, data, *field_delimiter, *record_delimiter);
                }
                fclose(data);
            }
        }
    }
    fclose(fpfmt);
}

/**
 * Returns file pointer after opening
 * Records delimiters used when there is only the format file
 * @param ac
 * @param av
 * @param field_delimiter
 * @param record_delimiter
 * @return file pointer
 */
FILE * open_file_set_delimiters(int ac, char *av[], char * field_delimiter, char * record_delimiter)
{
    FILE * fp;

    for(int i = 1; i < ac; i++) {
        if (av[i][0] == '-') { // Set delimiters
            set_delimiters(av, i, field_delimiter, record_delimiter);
        } else {
            if((fp = fopen(av[i], "r") ) == NULL )
                fatal("Can't open data file", "");
        }
    }

    return fp; // Return opened file
}

/**
 * Helper function to set delimiters
 * @param av
 * @param i
 * @param field_delimiter
 * @param record_delimiter
 */
void set_delimiters(char *av[], int i,
                    char * field_delimiter, char * record_delimiter)
{
    switch(av[i][1]){ // Read options
        case 'd': *field_delimiter = av[i][2];
            break;
        case 'D': *field_delimiter = '\n'; // New line option
            break;
        case 'r': case 'R': *record_delimiter = av[i][2];
            break;
    }
}

/**
 * Counts the number of files passed as argument
 * @param ac
 * @param av
 * @return num of files
 */
int count_files(int ac, char *av[])
{

    int file_count = 0;

    for(int i = 1; i < ac; i++){
        if(av[i][0] != '-'){ // Not an option
            file_count++;
        }
    }

    return file_count;
}

void fatal(char *s1, char *s2)
/*
 *	fatal error handler
 *	purpose: print error message to stderr then exit
 *	input:   two strings that are printed 
 *	never returns
 */
{
	fprintf(stderr, "%s: %s%s\n",  myname, s1, s2 );
	exit(1);
}
