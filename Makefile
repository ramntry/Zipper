all: z

z: main.o ZStream.o Zipper.o Unzipper.o zlib/libz.a
	g++ $^ -L./zlib -lz -o $@

.cpp.o:
	g++ -c -g3 $^ -o $@

zlib/libz.a:
	make -C zlib

clean:
	rm *.o

