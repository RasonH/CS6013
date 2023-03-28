CXX = c++
CFLAGS = -std=c++17
OBJS = Allocator.o MyHashTable.o main.o

all:
	make malloc
	./malloc

malloc: $(OBJS)
	$(CXX) $(OBJS) -o malloc

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

Allocator.o: Allocator.cpp Allocator.h
	$(CXX) $(CFLAGS) -c Allocator.cpp

MyHashTable.o: MyHashTable.cpp MyHashTable.h
	$(CXX) $(CFLAGS) -c MyHashTable.cpp

.PHONY:clean
clean:
	rm -rf *.o *.out malloc