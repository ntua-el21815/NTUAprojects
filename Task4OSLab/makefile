all:
	@echo "To compile the program use make compile."
	@echo "To delete the executables created use make clean."
compile: compile_main
clean: clean_main
compile_debug:
	@gcc -g parent.c tools.c -o ask3 -D DEBUG
	@echo "ask3 executable compiled succesfuly"
	@echo "Type ./ask3 <nChildren> [--random] [--round-robin] to run the program."
compile_main: main.c
	@gcc main.c tools.c -o ask4
	@echo "ask4 executable compiled succesfuly"
	@echo "Type ./ask4 to run the program."
clean_main:
	@rm ask4
	@echo "ask4 executable deleted."
	
