compile: compile_father compile_child
clean: clean_child clean_father
compile_father: father.c
	gcc father.c -o gates
compile_child:
	gcc child.c -o childexec
clean_child:
	rm childexec
clean_father:
	rm gates
	
