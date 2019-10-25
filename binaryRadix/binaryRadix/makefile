objects=main.o binaryRadix.o
binaryRadix_:$(objects)
	cc -o binaryRadix_ $(objects)
main.o:binaryRadix.h
avltree.o:binaryRadix.h

.PHONY:clean
clean:
	rm binaryRadix_$(objects)