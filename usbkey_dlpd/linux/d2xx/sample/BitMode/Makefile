TOPDIR  := $(shell cd ..; pwd)
include $(TOPDIR)/Rules.make

APP = bitmode

all: $(APP)

$(APP): main.c	
	$(CC) -o $(APP) $(CFLAGS) main.c	
	
clean:
	rm -f *.o ; rm $(APP)
