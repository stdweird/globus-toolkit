#include "gaa_util.h"
#include <strings.h>
#include <string.h>
#include <stdio.h>

/*
 * gaautil_gettok -- this is conceptually similar to "strtok".
 * Finds (and returns) the first non-whitespace character in "buf",
 * setting the first whitespace character after that to null.  Sets
 * next to a pointer to the first character after the one it nulled
 * out (or to the null character at the end of "buf", if this was
 * the last token).  Returns 0 if there are no more tokens.
 */

char *
gaautil_gettok(char *buf, char **next)
{
    char *s;

    if (buf == 0 || next == 0)
	return(0);

    if (*buf == '\0')
	return(0);

    while (isspace(*buf))
	buf++;
    
    s = buf;
    while (! isspace(*s))
	s++;
    if (*s != '\0')
	*s++ = '\0';
    *next = s;
    return(*buf == '\0' ? 0 : buf);
}
