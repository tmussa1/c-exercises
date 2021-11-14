#include	"ws13.h"
/*
 *	some constants
 */

#define	MAXFLD	40
#define	MAXVAL	120

/*
 *	function declarlations
 */

int	get_record(symtab_t *, FILE *);
void mailmerge( symtab_t *, FILE *);
int	process(FILE*, FILE*);
void fatal(char *, char *);
