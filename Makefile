

all: obj/main.o obj/pages.o bin/paiger

bin/paiger: obj/main.o obj/pages.o
	mkdir -p bin
	${CXX} obj/main.o obj/pages.o -o bin/paiger -lncurses

obj/main.o: src/main.cpp
	mkdir -p obj
	${CXX} -c src/main.cpp -o obj/main.o

obj/pages.o: src/pages.cpp
	mkdir -p obj
	${CXX} -c src/pages.cpp -o obj/pages.o

clean:
	rm obj/main.o obj/pages.o bin/paiger
