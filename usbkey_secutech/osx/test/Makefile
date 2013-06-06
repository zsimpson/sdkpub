all: testOld testNew

clean: 
	rm -f testOld testNew32 testNew64

testOld:
	g++ -m32 -mmacosx-version-min=10.4 testkey.cpp ../lib2009/UniKey.a -framework CoreFoundation -framework IOKit -o testOld

testNew:
	g++ -m32 -mmacosx-version-min=10.5 testkey.cpp ../lib2010/UniKey.a -framework CoreFoundation -framework IOKit -o testNew32
	g++ -m64 -mmacosx-version-min=10.5 testkey.cpp ../lib2010/UniKey.a -framework CoreFoundation -framework IOKit -o testNew64
