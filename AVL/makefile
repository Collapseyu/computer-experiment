objects=main.o avltree.o
AVL_:$(objects)
	cc -o AVL_ $(objects)
main.o:avltree.h
avltree.o:avltree.h

.PHONY:clean
clean:
	rm AVL_$(objects)