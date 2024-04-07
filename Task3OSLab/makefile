all:
	@echo "To compile the program use make compile."
	@echo "To delete the executables created use make clean."
compile: compile_parent
clean: clean_parent
compile_debug:
	@gcc -g parent.c tools.c -o ask3 -D DEBUG
	@echo "ask3 executable compiled succesfuly"
	@echo "Type ./ask3 <nChildren> [--random] [--round-robin] to run the program."
compile_parent: parent.c
	@gcc parent.c tools.c -o ask3
	@echo "ask3 executable compiled succesfuly"
	@echo "Type ./ask3 <nChildren> [--random] [--round-robin] to run the program."
clean_parent:
	@rm ask3
	@echo "ask3 executable deleted."
	
