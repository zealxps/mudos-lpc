#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "std.h"
#include "simulate.h"

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

char *reserved_area; /* reserved for MALLOC() */

char *xalloc(int size)
{
	char *p;
	static int going_to_exit;

	if (going_to_exit) {
		exit(3);
	}
#ifdef DEBUG
	if (size == 0) {/*      Tried to allocate 0 bytes.         */
		fatal("Error: Tried to allocate 0 bytes.\n");
	}
#endif 
	p = (char*)DMALLOC(size, TAG_MISC, "main.c: xalloc");
	if (p == 0) {
		if (reserved_area) {
			FREE(reserved_area);
			/*   Temporarily out of MEMORY. Freeing reserve.\n            */

			const char *err = "Error:Temporarily out of MEMORY. Freeing reserve.\n";
			write(1, err, strlen(err) );
			reserved_area = 0;
			return xalloc(size); /* Try again */
		}
		going_to_exit = 1;
		/*     Totally out of MEMORY.          */
		fatal("Totally out of MEMORY:.\n");
	}
	return p;
}
