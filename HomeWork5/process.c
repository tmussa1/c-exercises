#include	<stdio.h>
#include	"fl.h"
#include	"ws13.h"

/**
 *	process(fmt, data)
 *
 *	Purpose: read from datafile, format and output selected records
 *	Input:   fmt 		- input stream from format file
 *		 data		- stream from datafile
 *	Returns: 0
 *	Output:  copied fmt to stdout with insertions
 *	Errors:  not reported, functions call fatal() and die
 *	history: 2020-11-06 added int type and return 0 (10q VP)
 *	history: 2012-11-28 added free_table (10q BW)
 **/
int process(FILE *fmt, FILE *data)
{
	symtab_t *tab;

	if ( (tab = new_table()) == NULL )
		fatal("Cannot create storage object","");

	while ( get_record(tab,data) != NO )/* while more data	*/
	{
		mailmerge( tab, fmt );		/* merge with format	*/
		clear_table(tab);		/* discard data		*/
	}

	free_table(tab);			/* no memory leaks!	*/
	return 0;
}

