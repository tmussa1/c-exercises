#include	<stdio.h>
#include	<stdlib.h>
#include	<ctype.h>
#include	"wl.h"
#include	<string.h>

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
char * read_word();

int
main()
{
	char * wordptr;

	/* ... set up word filing module ... */

	init_table();	

	/* ... read words and store them ... */

    // Read arbitrary number of characters in a word
	while ((wordptr = read_word())){
		convert_to_lower_case( wordptr );
		if ( in_table( wordptr ) == YES )
			update( wordptr, 1 + lookup( wordptr ) );
		else if ( insert( wordptr, 1 ) == NO ){
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

/**
 * Reads arbitrary length of a word
 * @return char pointer
 */
char * read_word()
{
    int c, CHUNK_SIZE = 10, WORD_LENGTH = 0, ARRAY_SIZE = 0;
    char * word = NULL;

    while((c = getchar()) != EOF)
    {
        if(isspace(c) || c == EOF){

            if(WORD_LENGTH > 0){ // Found word
                word[WORD_LENGTH] = '\0';
                return strdup(word);
            }

        } else {

            if(WORD_LENGTH >= ARRAY_SIZE - 2){
                // Allocate enough space to contain the word
                ARRAY_SIZE += CHUNK_SIZE;
                word = realloc(word, ARRAY_SIZE);
            }

            word[WORD_LENGTH++] = c; // Copy the character
        }
    }

    return NULL;
}
