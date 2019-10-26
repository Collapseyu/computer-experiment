objects=main.o avltree.o
btree_search:$(objects)
	cc -o btree_search $(objects)
main.o:avltree.h
avltree.o:avltree.h

.PHONY:clean
clean:
	rm btree_search$(objects)