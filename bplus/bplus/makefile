objects=main.o BPlusTree.o
BPLUS_:$(objects)
	cc -o BPLUS_ $(objects)
main.o:BPlusTree.h
avltree.o:BPlusTree.h

.PHONY:clean
clean:
	rm BPLUS_$(objects)