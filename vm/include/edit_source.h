#ifndef EDIT_SOURCE_H
	#define EDIT_SOURCE_H

	extern FILE *yyin;
	void yyerror(const char *str);
	void mf_fatal(const char *str);
	int yyparse();

#endif
