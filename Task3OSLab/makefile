all:
	@echo "To compile the program use make compile."
	@echo "To delete the executables created use make clean."
compile: compile_parent
clean: clean_parent
compile_parent: parent.c
	@gcc parent.c tools.c -o parent
	@echo "parent executable compiled succesfuly"
	@echo "Type ./parent to run the program."
clean_parent:
	@rm parent
	@echo "parent executable deleted."
	
