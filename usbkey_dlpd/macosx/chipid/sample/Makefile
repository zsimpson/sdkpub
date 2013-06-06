include Rules.make

APP = ChipID

all: $(APP)

$(APP): ChipID.cpp	
	$(CC) -o $(APP) $(CFLAGS) ChipID.cpp
	
clean:
	rm -f *.o ; rm $(APP)
