
.PHONY: check-syntax
check-syntax:
	$(CC) $(INCLUDES) $(CCFLAGS) -S $(SRC)

.PHONY: check
check:
	cppcheck --max-configs=1000 --enable=all -q --suppress=missingIncludeSystem .

