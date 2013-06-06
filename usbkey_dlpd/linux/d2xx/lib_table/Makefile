# which compiler
CC = gcc

VERSION = _RELEASE

LIBNAME = libd2xx_table.so

CFLAGS =  -DLINUX -D$(VERSION)

$(LIBNAME):	ftdi_table.o 

	$(CC) 	-Wall -shared -fPIC -o  $(LIBNAME) ftdi_table.o

ftdi_table.o:	ftdi_table.c
		$(CC) -I. $(CFLAGS) -c -fPIC ftdi_table.c

clean:
	rm -f *.o ; rm $(LIBNAME)

#gcc -c -fPIC ftdi_table.c ; gcc -shared -fPIC -o libftd.so ftdi_table.o
