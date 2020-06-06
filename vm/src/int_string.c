#include <string.h>

#include "std.h"
#include "stralloc.h"
#include "simulate.h"

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
int max_string_length;

#ifdef DEBUGMALLOC
char *int_string_copy(const char *str, char *desc)
#else 
char *int_string_copy(const char *str)
#endif 
{
	char *p;
	int len;

	/*    Null string passed to string_copy.\n           */
	DEBUG_CHECK(!str, "Null string passed to string_copy.\n");
	len = strlen(str);
	if (len > max_string_length)
	{
		len = max_string_length;
		p = new_string(len, desc);
		(void)strncpy(p, str, len);
		p[len] = '\0';
	}
	else
	{
		p = new_string(len, desc);
		(void)strncpy(p, str, len + 1);
	}
	return p;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

#ifdef DEBUGMALLOC
char *int_string_unlink(char *str, char *desc)
#else 
char *int_string_unlink(char *str)
#endif 
{
	malloc_block_t *mbt,  *newmbt;

	mbt = ( (malloc_block_t*)str) - 1;
	mbt->ref--;

	if (mbt->size == USHRT_MAX)
	{
		int l = strlen(str + USHRT_MAX) + USHRT_MAX; /* ouch */

		newmbt = (malloc_block_t*)DXALLOC(l + sizeof(malloc_block_t) + 1, TAG_MALLOC_STRING, desc);
		memcpy( (char*) (newmbt + 1), (char*) (mbt + 1), l + 1);
		newmbt->size = USHRT_MAX;
		ADD_NEW_STRING(USHRT_MAX, sizeof(malloc_block_t) );
	}
	else
	{
		newmbt = (malloc_block_t*)DXALLOC(mbt->size + sizeof(malloc_block_t) + 1, TAG_MALLOC_STRING, desc);
		memcpy( (char*) (newmbt + 1), (char*) (mbt + 1), mbt->size + 1);
		newmbt->size = mbt->size;
		ADD_NEW_STRING(mbt->size, sizeof(malloc_block_t) );
	}
	newmbt->ref = 1;
	CHECK_STRING_STATS;

	return (char*) (newmbt + 1);
}
