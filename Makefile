CC ?= gcc

all:
	$(CC) section.c -T section.lds -o section


clean:
	rm -rf section
