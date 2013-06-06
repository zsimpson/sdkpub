# which compiler
CC = gcc

SUBDIRS = BitMode EEPROM/erase EEPROM/read EEPROM/write EEPROM/user/read \
	  EEPROM/user/size EEPROM/user/write Events LargeRead \
	  SetVIDPID Simple Timeouts W32/escapeseq W32/events W32/simple W32/timeouts \
	  W32/unsupported
	  
all: subdirs

subdirs:
	for n in $(SUBDIRS); do $(MAKE) -C $$n || exit 1; done

clean:
	rm -f *.o *~
	for n in $(SUBDIRS); do $(MAKE) -C $$n clean; done
	
