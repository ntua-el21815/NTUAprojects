all:
	@echo "To compile the program use make compile."
	@echo "To delete the executables created use make clean."
compile: compile_main
clean: clean_main
compile_main: main.c
	@gcc main.c tools.c -o ask4
	@echo "ask4 executable compiled succesfuly"
	@echo "Type ./ask4 to run the program."
clean_main:
	@rm ask4
	@echo "ask4 executable deleted."
	
