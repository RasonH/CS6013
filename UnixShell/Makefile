shell: main.o shelpers.o
	c++ --std=c++14 -o shell main.o shelpers.o

main.o : main.cpp shelpers.hpp
	c++ --std=c++14 -c main.cpp

shelpers.o : shelpers.cpp shelpers.hpp
	c++ --std=c++14 -c shelpers.cpp

.PHONY: clean
clean :
	rm -f main.o shelpers.o shell