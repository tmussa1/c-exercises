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

int count_files(int, char *[]);
void process_arguments(int, char * [], char *, char *);

int main(int ac, char *av[])
{
	myname = *av;
    char field_delimiter = ';', record_delimiter = '\n';

	/*
	 * 	check that there is at least one arg: the format file
	 */

	if ( ac == 1 )
		fatal("usage: fl format [datafile..]","");

    process_arguments(ac, av, &field_delimiter, &record_delimiter);

	/* ... process data from stdin ... */
    // TODO - read multiple files
    // TODO - this may count a - option, options and fmt may come in any order

	return 0;
}

/**
 * Processes command line arguments
 * @param fpfmt , @param ac , @param av , @param field_delimiter , @param record_delimiter
 */
void process_arguments(int ac, char *av[],
                       char * field_delimiter, char * record_delimiter)
{
    if(count_files(ac, av) == 1) // Read from stdin if only format is passed
    {
        FILE * fp;

        for(int i = 1; i < ac; i++) {
            if (av[i][0] == '-') {
                switch(av[i][1]) {
                    case 'd':
                        *field_delimiter = av[i][2];
                        break;
                    case 'D':
                        *field_delimiter = '\n';
                        break;
                    case 'r':
                    case 'R':
                        *record_delimiter = av[i][2];
                        break;
                }
            } else {
                if((fp = fopen(av[i], "r") ) == NULL )
                    fatal("Can't open data file", "");
            }
        }
        process(fp, stdin, *field_delimiter, *record_delimiter);
    }
    else {

        FILE *fpfmt = NULL;

        for(int i = 1; i < ac; i++){
            if(av[i][0] == '-'){
                switch(av[i][1]){ // Read options
                    case 'd': *field_delimiter = av[i][2];
                        break;
                    case 'D': *field_delimiter = '\n';
                        break;
                    case 'r': case 'R': *record_delimiter = av[i][2];
                        break;
                }
            } else {

                if (fpfmt == NULL){
                    if((fpfmt = fopen(av[i], "r") ) == NULL )
                        fatal("Can't open data file", "");
                }
                else {
                      FILE * data;
                      // Read and process files
                      if ( (data = fopen(av[i], "r") ) == NULL )
                          fatal("Can't open data file", "");
                      else {
                          process(fpfmt, data, *field_delimiter, *record_delimiter);
                      }
                      fclose(data);
                }
            }
        }
        fclose(fpfmt);
    }
}

/**
 * Counts the number of files passed as argument
 * @param ac
 * @param av
 * @return
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
