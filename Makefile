#---------------------------------------------------------------
# Makefile of QTZ-Online-Game-Server-OS
PROJ_DIR ?= $(shell pwd)
PROJ_NAME ?= lpc-egg
GAME_BIN ?= engine
COMPILE_USER = $(PROJ_NAME)

all: build

include $(PROJ_DIR)/mk/lpc.mk
include $(PROJ_DIR)/mk/platform.mk

# 在这里添加需要编译的选项
build: predo lpcvm depend $(PROJ_NAME)

# 在这里添加工程需要include的目录
PROJ_INCLUDES := -I$(VMDIR) \
	-I$(VMDIR)/include \
	-Isrc/startup/ 

# 在这里添加工程需要的静态库
PROJ_STATIC_LIBS := $(VMLIB)

# 在这里添加工程需要编译的目录
PROJ_COMPILE_DIRS := src/ \
	src/startup/ \
	$(shell cat ./modules/list.txt)

INCLUDES := $(INCLUDES) $(PROJ_INCLUDES)
STATIC_LIBS := $(PROJ_STATIC_LIBS) $(STATIC_LIBS)
COMPILE_DIRS := $(COMPILE_DIRS) $(PROJ_COMPILE_DIRS)

OBJDIR=.obj
SRC:= $(foreach v, $(COMPILE_DIRS), $(wildcard $(v)/*.c))
OBJ=$(addprefix $(OBJDIR)/,$(subst .c,.o,$(SRC)))
DEPS := $(OBJ:.o=.d)

$(OBJDIR)/%.o: %.c 
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTIMIZE) -o $@ -c $<

$(OBJDIR)/%.d: %.c
	@$(CC) -MM -MG $(CFLAGS) $(INCLUDES) $< | sed -e 's,^\([^:]*\)\.o[ ]*:,$(@D)/\1.o $(@D)/\1.d:,' >$@

depend: $(DEPS) 

.PHONY : predo
predo:
	@test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	$(foreach v, $(COMPILE_DIRS), $(shell mkdir -p $(OBJDIR)/$(v)))

$(PROJ_NAME):  $(STATIC_LIBS) $(OBJ)
	$(PROOF) $(CC) $(CFLAGS) $(OPTIMIZE) -o $@ $(OBJ) $(STATIC_LIBS) $(EXTRALIBS)
	-cp $(PROJ_NAME) $(GAME_BIN).nostrip
	-cp $(GAME_BIN).nostrip $(GAME_BIN)
	-strip $(GAME_BIN)

.PHONY : clean
clean:
	-rm -f $(GAME_BIN) $(GAME_BIN).nostrip
	-rm -rf $(OBJDIR)
	-rm -rf $(PROJ_NAME)

cleanall: clean lpcvm-clean
