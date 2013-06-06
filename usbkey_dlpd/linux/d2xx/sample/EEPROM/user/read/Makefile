TOPDIR  := $(shell cd ..;  cd ..; cd ..; pwd)
include $(TOPDIR)/Rules.make

APP = readua

all: $(APP)

$(APP): main.c	
	$(CC) -o $(APP) $(CFLAGS) main.c	
	
clean:
	rm -f *.o ; rm $(APP)
