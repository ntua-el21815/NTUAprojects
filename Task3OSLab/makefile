all:
	@echo "To compile the program use make compile."
	@echo "To delete the executables created use make clean."
compile: compile_child compile_parent
clean: clean_child clean_parent
compile_parent: parent.c
	@gcc parent.c -o parent
	@echo "parent executable compiled succesfuly"
	@echo "Type ./parent to run the program."
compile_child:
	@gcc child.c -o childexec
	@echo "Child executable (childexec) compiled succesfully."
	@echo "To ensure program runs correctly don't delete childexec."
clean_child:
	@rm childexec
	@echo "Child executable deleted."
clean_parent:
	@rm parent
	@echo "parent executable deleted."
	
