objects=main.o BPlusTree.o
bplus_search:$(objects)
	cc -o bplus_search $(objects)
main.o:BPlusTree.h
avltree.o:BPlusTree.h

.PHONY:clean
clean:
	rm bplus_search$(objects)