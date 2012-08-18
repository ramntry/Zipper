all: z

z: main.cpp zlib/libz.a
	g++ -g3 $^ -L./zlib -lz -o $@

zlib/libz.a:
	make -C zlib

