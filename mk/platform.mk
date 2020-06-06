SHELL		= /bin/sh
INSTALL		= install -c
YACC		= bison -d -y --no-lines
RANLIB		= ranlib
PROOF		=
STRFUNCS	=

OS = $(shell uname)

# OS Darwin
# ===========================
ifeq ($(OS), Darwin)
export MACOSX_DEPLOYMENT_TARGET=10.10
CC		= clang
MAKE		= make
CPP		= clang -E
INCLUDES	= -I/usr/lib/clang/3.0/include\
		-I/usr/local/include  \
		-I/usr/include \
		-I/usr/include/apr-1 \
		-I/opt/local/include \
		-I/usr/include/sasl \
		-I/usr/local/include/libbson-1.0 \
		-I/usr/local/include/libmongoc-1.0/ \
		-I/opt/local/libexec/llvm-3.0/include -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS

CFLAGS		= -g3 -Wall -DDBVAR_NOASSIGN ${DEFINE_MACROS} -DUSE_LLVM -Wunused-function #-DDEBUG
EDIT_CFLAGS	= -g3  
OPTIMIZE	= -pipe -march=native  -DFD_SETSIZE=10000 -Wall -D_THREAD_SAFE -g 
EXTRALIBS	= -L/opt/local/lib/db46 \
		-L/opt/local/lib \
		-L/usr/local/lib  \
		-L/usr/lib \
		-lmongoc-1.0.0 -lbson-1.0.0 \
		-lpthread -lm\
		-lapr-1 -levent -lcrypto \
		-lm \
		-lsasl2 \
		-lssl -lcrypto -lz -liconv \
		-lcurl -lintl
else 


# OS Linux
# ====================
ifeq ($(OS), Linux)
CC		= gcc
MAKE		= gmake

INCLUDES	:= -I/usr/include/ \
			-I/usr/local/include \
			-I/usr/lib/gcc/x86_64-redhat-linux/4.4.4/include \
			-I/usr/local/ssl/include/ \
			-I/usr/include/apr-1/


EXTRALIBS	= -L/usr/local/ssl/lib 			\
		-L/usr/lib 					\
		-L/usr/lib64					\
		-L/usr/local/lib				\
		-L/usr/lib/lib 				\
		-L/usr/local/apr/lib/ \
		-Wl,-Bstatic \
		-liconv  						\
		-lapr-1 						\
		-levent 						\
		-lssl							\
		-lcrypto 						\
		-lrt    						\
		-lm 							\
		-Wl,-Bdynamic \
		-ldl    						

CPP		= gcc -E
OPTIMIZE = -pthread -O2 -pipe -DFD_SETSIZE=10000 -Wall -D_THREAD_SAFE -fstrength-reduce
CFLAGS		= -g3 -Wall -D__linux__ -DUSE_JE_MALLOC -DDBVAR_NOASSIGN -D_GNU_SOURCE ${DEFINE_MACROS} -DBUILD_DATE="\"$(shell LANG=en_US.UTF-8 date)\"" -fgnu89-inline
EDIT_CFLAGS	= -g3 
else



# OS freebsd, or other etc.
# =========================
OS_VERSION = $(shell uname -r)
ifeq ($(OS_VERSION), 8.2-RELEASE)
CC      = gcc44
else
CC		= clang
endif
MAKE		= gmake
INCLUDES	= -I/usr/local/include
EXTRALIBS	= -L/usr/lib -L/usr/local/lib  -L/usr/local/lib/mysql -R/usr/local/lib -lapr-1 -levent -static  -lthr -lcrypt -lm -lmd /usr/local/lib/libcurl.a -L/usr/lib/lib -lssl -lcrypto -lz -liconv -lstdc++ -l intl -Lpackages/db/mongo-c-driver/ -lmongoc  
CPP		= gcc44 -E
CFLAGS		= -g -Wall -DDBVAR_NOASSIGN ${DEFINE_MACROS}
EDIT_CFLAGS	= -g
OPTIMIZE	= -pipe -march=native -fprefetch-loop-arrays -DFD_SETSIZE=10000 -Wall -D_THREAD_SAFE -fomit-frame-pointer -fstrength-reduce -g
endif
endif

