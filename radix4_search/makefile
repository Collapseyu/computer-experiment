objects=main.o 4BinaryRad.o
radix4_search:$(objects)
	cc -o radix4_search $(objects)
main.o:4BinaryRad.h
avltree.o:4BinaryRad.h

.PHONY:clean
clean:
	rm radix4_search$(objects)