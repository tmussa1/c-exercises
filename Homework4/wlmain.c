#include	<stdio.h>
#include	<stdlib.h>
#include	<ctype.h>
#include	"wl.h"

/*
 *	wordlist	main module
 *
 *	program reads words from standard input until EOF
 *	then prints all words it saw with the number of times
 *	each word appeared.  Order is order of appearance.
 *
 *	calls functions in a filer module to store and retrieve
 *	the words.
 *
 *	history: modified 11.11.00 to answer all -Wall warnings
 */

/*
 *	definitions and declarations are in wl.h
 */

void convert_to_lower_case(char *);
int
main()
{
	char	buf[BUFLEN], *wordptr;

	/* ... set up word filing module ... */

	init_table();	

	/* ... read words and store them ... */

	while ( scanf("%s", buf) == 1 ){
		convert_to_lower_case( buf );
		if ( in_table( buf ) == YES )
			update( buf, 1 + lookup( buf ) );
		else if ( insert( buf, 1 ) == NO ){
			fprintf(stderr,"wordfreq: out of memory\n");
			exit(1);
		}
	}

	/* ... move cursor down the table printing out results */

	for( wordptr = firstword() ; wordptr != NULL; wordptr = nextword() )
		printf("%5d\t%s\n", lookup( wordptr ), wordptr );

	return 0;
}

/*
 * this function converts any string to all lower-case
 * letters.  Right now it is not being used since
 * the script that calls this program converts the text
 * anyway.
 */

void
convert_to_lower_case( char *str )
{
	while( *str )
	{
		*str = tolower( (int) *str );
		str++;
	}
}
