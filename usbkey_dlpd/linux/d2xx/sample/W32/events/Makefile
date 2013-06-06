TOPDIR  := $(shell cd ..; cd ..; pwd)
include $(TOPDIR)/Rules.make

APP = w32_events

all: $(APP)

$(APP): main.c	
	$(CC) -o $(APP) $(CFLAGS) main.c -lpthread	
	
clean:
	rm -f *.o ; rm $(APP)
