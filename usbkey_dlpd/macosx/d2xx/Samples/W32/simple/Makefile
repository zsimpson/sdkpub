TOPDIR  := $(shell cd ..; cd ..; pwd)
include $(TOPDIR)/Rules.make

APP = w32_simple

all: $(APP)

$(APP): main.c	
	$(CC) -o $(APP) $(CFLAGS) -g main.c
	
clean:
	rm -f *.o ; rm $(APP)
