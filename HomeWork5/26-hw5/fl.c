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

int main(int ac, char *av[])
{
	FILE *fpfmt;
	myname = *av;

	/*
	 * 	check that there is at least one arg: the format file
	 */

	if ( ac == 1 )
		fatal("usage: fl format [datafile..]","");

	/*
	 *	then try to open it
	 */

	if (  (fpfmt = fopen( av[1] , "r")) == NULL )
		fatal("Cannot open format file:", av[1]);

	/*
	 *	in full version, code to handle names of data files
	 *	on the command line will appear here
	 */

	/* ... process data from stdin ... */

	process(fpfmt, stdin);
	fclose(fpfmt);
	return 0;
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
