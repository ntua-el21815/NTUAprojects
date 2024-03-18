all:
	@echo "To compile the program use make compile."
	@echo "To delete the executables created use make clean."
compile: compile_child compile_father
clean: clean_child clean_father
compile_father: father.c
	@gcc father.c -o gates
	@echo "gates executable compiled succesfuly"
	@echo "Type ./gates to run the program."
compile_child:
	@gcc child.c -o childexec
	@echo "Child executable (childexec) compiled succesfully."
	@echo "To ensure program runs correctly don't delete childexec."
clean_child:
	@rm childexec
	@echo "Child executable deleted."
clean_father:
	@rm gates
	@echo "gates executable deleted."
	
