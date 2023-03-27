CXX = c++
CFLAGS = -std=c++17
OBJS = MyMalloc.o HashTable.o main.o

all:
	make malloc

malloc: $(OBJS)
	$(CXX) $(OBJS) -o malloc

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

MyMalloc.o: MyMalloc.cpp MyMalloc.h
	$(CXX) $(CFLAGS) -c MyMalloc.cpp

HashTable.o: HashTable.cpp HashTable.h
	$(CXX) $(CFLAGS) -c HashTable.cpp

.PHONY:clean
clean:
	rm -rf *.o *.out malloc