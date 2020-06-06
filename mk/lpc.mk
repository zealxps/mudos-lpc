PROJ_DIR ?= ../
VMDIR=$(PROJ_DIR)/vm
VMLIB=$(VMDIR)/lpcvm.a
PACKAGES_SPEC=$(shell pwd)/.spec

.PHONY : lpcvm lpcvm-clean

lpcvm:
	@test -d $(PACKAGES_SPEC) || mkdir -p $(PACKAGES_SPEC)
	@rm -rf $(PACKAGES_SPEC)/*
	@for v in $(PROJ_COMPILE_DIRS); do \
		test -d $$v/spec && cp -p $$v/spec/* $(PACKAGES_SPEC); \
		continue; \
		done
	@$(MAKE) -C $(VMDIR) all PACKAGES_SPEC_PATH=$(PACKAGES_SPEC)
	@echo "lpcvm ok!"


lpcvm-clean:
	$(MAKE) -C $(VMDIR) clean
	-rm -rf $(PACKAGES_SPEC)


.PHONY: check-syntax 
check-syntax: 
	$(CC) $(INCLUDES) $(CCFLAGS) -S $(SRC)

.PHONY: check
check:
	cppcheck --max-configs=1000 --enable=all -q --suppress=missingIncludeSystem .
