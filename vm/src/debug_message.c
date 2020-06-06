#include <stdio.h>
#include <config.h>
#include <string.h>

#include "std.h"
#include "file_incl.h"


//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

int _Touch(const char *PathFile)
{
	struct stat st;
	char TempDir[strlen(PathFile) + 1];
	const char *Start,  *Index;
	int fd;
	if (stat(PathFile, &st) !=  - 1)
	{
		return 1;
	}

	Start = PathFile;
	Index = NULL;
	while ( (Index = strchr(Start, '/') ) != NULL)
	{
		strlcpy(TempDir, PathFile, Index - PathFile + 1);
		Start = Index + 1;
		mkdir(TempDir, 0755);
	} 

	fd = open(PathFile, O_WRONLY | O_CREAT, 0644);
	if (fd !=  - 1)
	{
		close(fd);
		return 1;
	}
	else
	{
		return 0;
	}
}

char *format_time(time_t tm)
{
	static char strtime[30];
	strftime(strtime, 30, "%Y-%m-%d %H:%M:%S", localtime(&tm) ); //strftime会添加\0
	return strtime;
}

//-------------------------------------------------------------------------
//
//-------------------------------------------------------------------------

char *log_dir = 0; 
void debug_message(const char *fmt, ...)
{
	static int append = 0;
	static char deb_buf[100];
	static char *deb = deb_buf;
	time_t tm;
	va_list args;
	FILE *fp = NULL;
	V_DCL(char *fmt);

    if(!log_dir) {
        goto end; 
    }


	if (!append) {
        extern int run_flag;
        if ( run_flag )
        {
        	snprintf(deb, sizeof(deb_buf), "%s/r_%s", log_dir, DEBUG_LOG_FILE);
        }
        else
        {
        	snprintf(deb, sizeof(deb_buf), "%s/%s", log_dir, DEBUG_LOG_FILE);
        }
	}

	_Touch(deb);
	fp = fopen(deb, append ? "a" : "w");

	/*
	 * re-use stdout's file descriptor if system or process runs out
	 *
	 * OS/2 doesn't have ENFILE.
	 */
	if (!fp && (errno == EMFILE 
#ifdef ENFILE
				|| errno == ENFILE 
#endif 
		   ) ) {
		fp = freopen(deb, append ? "a" : "w", stdout);
		append = 2;
	} else {
		append = 1;
	}

	if (!fp) {
		/* darn.  We're in trouble */
		perror(deb);
		abort();
	}
	time(&tm);

	fprintf(fp, "%s\t", format_time(tm) );
	V_START(args, fmt);
	V_VAR(char *, fmt, args);
	vfprintf(fp, fmt, args);
	fflush(fp);
	va_end(args);

	/*
	 * don't close stdout
	 */
	if (append != 2) {
		(void)fclose(fp);
	}

end:
	V_START(args, fmt);
	V_VAR(char *, fmt, args);
	vfprintf(stderr, fmt, args);
	fflush(stderr);
	va_end(args);
}

