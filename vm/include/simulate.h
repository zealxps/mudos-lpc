#ifndef SIMULATE_H
#define SIMULATE_H

#include "object.h"
#include "array.h"

#define V_SHORT         1
#define V_NOSPACE       2
#define V_FUNCTION      4

/* The end of a static buffer */
#define EndOf(x) (x + sizeof(x)/sizeof(x[0]))

/*
 * simulate.c
 */

extern int illegal_sentence_action;
extern object_t *obj_list;
extern object_t *obj_list_destruct;
extern object_t *current_object;
extern object_t *command_giver;
extern object_t *current_interactive;
extern char *inherit_file;
extern int tot_alloc_sentence;

char *strput(char *, char *,const char*);
char *strput_int(char *, char *, int);
void debug_fatal(char *, ...);
void fatal(const char *, ...);
void error(const char *, ...);
INLINE void check_legal_string(char*);
void free_sentence(sentence_t*);

//int input_to(svalue_t *, int, int, svalue_t*);
int get_char(svalue_t *, int, int, svalue_t*);

int strip_name(const char *, char *, int);
char *check_name(char*);

#define load_object(x, y) int_load_object(x, 0)
object_t *int_load_object(const char*, int);

object_t *clone_object(char *, int);
object_t *find_object(const char*);
object_t *find_object2(const char*);
object_t *reload_object(const char*);
void move_object(object_t *, object_t*);
void destruct_object(object_t*);
void destruct2(object_t*);

void print_svalue(svalue_t*);
void error_needs_free(char*);
void throw_error(void);
void error_handler(char*);

#ifdef SIGNAL_FUNC_TAKES_INT
void startshutdownOS(int);
#else 
void startshutdownOS(void);
#endif 
void shutdown_os(int);
void slow_shut_down(int);

#ifdef DEBUGMALLOC_EXTENSIONS
void mark_free_sentences(void);
#endif 

#endif
