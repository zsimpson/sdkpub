CC=gcc
CFLAGS=-ldl -lpthread libftd2xx.a
APP = static_link

all: $(APP)

$(APP): main.c	
	$(CC) -o $(APP) main.c $(CFLAGS)	
	
clean:
	rm -f *.o ; rm $(APP)
