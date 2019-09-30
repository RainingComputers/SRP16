.PHONY : help
help :
	@echo "clean"
	@echo "      Remove auto-generated files."
	@echo "build"
	@echo "      Build the assembler to executable."
	@echo "debugbuild"
	@echo "      Build debug version"

clean:
	rm -f -r bin/
	rm -f -r obj/

obj/:
	mkdir obj/

bin/:
	mkdir bin/

obj/isa.o: src/isa.hpp src/isa.cpp obj/
	g++ -g -c src/isa.cpp -o obj/isa.o

obj/syntax.o: src/syntax.hpp src/syntax.cpp obj/
	g++ -g -c src/syntax.cpp -o obj/syntax.o

obj/log.o: src/log.hpp src/log.cpp
	g++ -g -c src/log.cpp -o obj/log.o

obj/main.o: obj/syntax.o obj/isa.o obj/log.o src/main.cpp obj/
	g++ -g -c src/main.cpp -o obj/main.o

debugbuild: obj/main.o bin/
	g++ -g -o bin/srp16asm obj/main.o obj/syntax.o obj/log.o obj/isa.o

build: bin/
	rm -f -r obj/
	g++ -c src/syntax.cpp	
	g++ -c src/main.cpp
	g++ -c src/isa.cpp
	g++ -c src/log.cpp
	g++ -o bin/srp16asm main.o syntax.o isa.o log.o
	rm -f *.o