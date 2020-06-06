/*
	This file is automatically generated by make_func.
	do not make any manual changes to this file.
*/


/* operators */

#define F_POP_VALUE                    1
#define F_PUSH                         2
#define F_EFUN0                        3
#define F_EFUN1                        4
#define F_EFUN2                        5
#define F_EFUN3                        6
#define F_EFUNV                        7
#define F_NUMBER                       8
#define F_REAL                         9
#define F_BYTE                         10
#define F_NBYTE                        11
#define F_STRING                       12
#define F_SHORT_STRING                 13
#define F_CONST0                       14
#define F_CONST1                       15
#define F_AGGREGATE                    16
#define F_AGGREGATE_ASSOC              17
#define F_BRANCH_WHEN_ZERO             18
#define F_BRANCH_WHEN_NON_ZERO         19
#define F_BRANCH                       20
#define F_BBRANCH_WHEN_ZERO            21
#define F_BBRANCH_WHEN_NON_ZERO        22
#define F_BBRANCH                      23
#define F_BRANCH_NE                    24
#define F_BRANCH_GE                    25
#define F_BRANCH_LE                    26
#define F_BRANCH_EQ                    27
#define F_BBRANCH_LT                   28
#define F_FOREACH                      29
#define F_NEXT_FOREACH                 30
#define F_EXIT_FOREACH                 31
#define F_LOOP_COND_LOCAL              32
#define F_LOOP_COND_NUMBER             33
#define F_LOOP_INCR                    34
#define F_WHILE_DEC                    35
#define F_LOR                          36
#define F_LAND                         37
#define F_CATCH                        38
#define F_END_CATCH                    39
#define F_TIME_EXPRESSION              40
#define F_END_TIME_EXPRESSION          41
#define F_SWITCH                       42
#define F_CALL_FUNCTION_BY_ADDRESS     43
#define F_CALL_INHERITED               44
#define F_RETURN                       45
#define F_RETURN_ZERO                  46
#define F_EQ                           47
#define F_NE                           48
#define F_LE                           49
#define F_LT                           50
#define F_GE                           51
#define F_GT                           52
#define F_INC                          53
#define F_DEC                          54
#define F_PRE_INC                      55
#define F_POST_INC                     56
#define F_PRE_DEC                      57
#define F_POST_DEC                     58
#define F_TRANSFER_LOCAL               59
#define F_LOCAL                        60
#define F_LOCAL_LVALUE                 61
#define F_UPVALUE                      62
#define F_UPVALUE_LVALUE               63
#define F_GLOBAL                       64
#define F_GLOBAL_LVALUE                65
#define F_MEMBER                       66
#define F_MEMBER_LVALUE                67
#define F_INDEX                        68
#define F_INDEX_LVALUE                 69
#define F_RINDEX                       70
#define F_RINDEX_LVALUE                71
#define F_NN_RANGE                     72
#define F_NN_RANGE_LVALUE              73
#define F_RN_RANGE                     74
#define F_RN_RANGE_LVALUE              75
#define F_RR_RANGE                     76
#define F_RR_RANGE_LVALUE              77
#define F_NR_RANGE                     78
#define F_NR_RANGE_LVALUE              79
#define F_NE_RANGE                     80
#define F_RE_RANGE                     81
#define F_ADD_EQ                       82
#define F_SUB_EQ                       83
#define F_AND_EQ                       84
#define F_OR_EQ                        85
#define F_XOR_EQ                       86
#define F_LSH_EQ                       87
#define F_RSH_EQ                       88
#define F_MULT_EQ                      89
#define F_DIV_EQ                       90
#define F_MOD_EQ                       91
#define F_ASSIGN                       92
#define F_VOID_ADD_EQ                  93
#define F_VOID_ASSIGN                  94
#define F_VOID_ASSIGN_LOCAL            95
#define F_ADD                          96
#define F_SUBTRACT                     97
#define F_MULTIPLY                     98
#define F_DIVIDE                       99
#define F_MOD                          100
#define F_AND                          101
#define F_OR                           102
#define F_XOR                          103
#define F_LSH                          104
#define F_RSH                          105
#define F_NOT                          106
#define F_NEGATE                       107
#define F_COMPL                        108
#define F_FUNCTION_CONSTRUCTOR         109
#define F_SIMUL_EFUN                   110
#define F_SSCANF                       111
#define F_PARSE_COMMAND                112
#define F_NEW_CLASS                    113
#define F_NEW_EMPTY_CLASS              114
#define F_EXPAND_VARARGS               115

/* 1 arg efuns */
#define BASE 116

#define F_TO_INT                       116
#define F_TO_FLOAT                     117
#define F_PREVIOUS_OBJECT              118
#define F_CALL_STACK                   119
#define F_SIZEOF                       120
#define F_DESTRUCT                     121
#define F_FILE_NAME                    122
#define F_RANDOM                       123
#define F_LOWER_CASE                   124
#define F_RELOAD_OBJECT                125
#define F_ALLOCATE_MAPPING             126
#define F_VALUES                       127
#define F_KEYS                         128
#define F_CLONEP                       129
#define F_INTP                         130
#define F_UNDEFINEDP                   131
#define F_FLOATP                       132
#define F_STRINGP                      133
#define F_FUNCTIONP                    134
#define F_POINTERP                     135
#define F_OBJECTP                      136
#define F_CLASSP                       137
#define F_TYPEOF                       138
#define F_BUFFERP                      139
#define F_REPLACE_PROGRAM              140
#define F_ALLOCATE                     141
#define F_FILE_SIZE                    142
#define F_RM                           143
#define F_RMDIR                        144
#define F_MD5_HEXDIGEST                145
#define F_CTIME                        146
#define F_LOCALTIME                    147
#define F_THROW                        148
#define F_DEEP_INHERIT_LIST            149
#define F_SHALLOW_INHERIT_LIST         150
#define F_MAPP                         151
#define F_CHILDREN                     152
#define F_ERROR                        153
#define F_SET_EVAL_LIMIT               154
#define F_LPC_GC                       155
#define F_FUNC_IN_EXAMPLE_LIB          156
#define F_COPY                         157
#define F_FILE_LENGTH                  158
#define F_UPPER_CASE                   159
#define F_FETCH_VARIABLE               160
#define F_FUNCTION_OWNER               161
#define F_REFS                         162
#define F_COS                          163
#define F_SIN                          164
#define F_TAN                          165
#define F_ASIN                         166
#define F_ACOS                         167
#define F_ATAN                         168
#define F_SQRT                         169
#define F_FLOOR                        170
#define F_CEIL                         171

/* efuns */
#define ONEARG_MAX 172

#define F_CALL_OTHER                   172
#define F_EVALUATE                     173
#define F_THIS_OBJECT                  174
#define F_CLONE_OBJECT                 175
#define F_EXPLODE                      176
#define F_IMPLODE                      177
#define F_MEMBER_ARRAY                 178
#define F_REPLACE_STRING               179
#define F_REPLACE_STRING_REG           180
#define F_RESTORE_OBJECT               181
#define F_SAVE_OBJECT                  182
#define F_GET_DIR                      183
#define F_STRSRCH                      184
#define F_SUBSTR                       185
#define F_FIND_OBJECT                  186
#define F_MAP_DELETE                   187
#define F_ALLOCATE_BUFFER              188
#define F_READ_BUFFER                  189
#define F_WRITE_BUFFER                 190
#define F_INHERITS                     191
#define F_REGEXP                       192
#define F_WRITE_FILE                   193
#define F_RENAME                       194
#define F_WRITE_BYTES                  195
#define F_READ_BYTES                   196
#define F_READ_FILE                    197
#define F_CP                           198
#define F_MKDIR                        199
#define F_CLEAR_BIT                    200
#define F_TEST_BIT                     201
#define F_SET_BIT                      202
#define F_NEXT_BIT                     203
#define F_FUNCTION_EXISTS              204
#define F_OBJECTS                      205
#define F_SORT_ARRAY                   206
#define F_TIME                         207
#define F_UNIQUE_MAPPING               208
#define F_SPRINTF                      209
#define F_STAT                         210
#define F_MEMORY_INFO                  211
#define F_UPTIME                       212
#define F_BOOT_TIME                    213
#define F_STRCMP                       214
#define F_FILTER_ARRAY                 215
#define F_FILTER_MAPPING               216
#define F_MAP_MAPPING                  217
#define F_MAP_ARRAY                    218
#define F_MALLOC_STATUS                219
#define F_DUMPALLOBJ                   220
#define F_DUMP_FILE_DESCRIPTORS        221
#define F_QUERY_LOAD_AVERAGE           222
#define F_RECLAIM_OBJECTS              223
#define F_SHUTDOWN                     224
#define F_OS_COMMAND                   225
#define F_FS_MEMORY_INFO               226
#define F_GET_HOST_IP                  227
#define F_FUNCTIONS                    228
#define F_VARIABLES                    229
#define F_REPLACEABLE                  230
#define F_PROGRAM_INFO                 231
#define F_STORE_VARIABLE               232
#define F_DEBUG_MESSAGE                233
#define F_REPEAT_STRING                234
#define F_DEBUG_INFO                   235
#define F_DUMP_PROG                    236
#define F_POW                          237
#define F_MAX_ARRAY                    238
#define F_MIN_ARRAY                    239

/* efuns */
#define NUM_OPCODES 239
