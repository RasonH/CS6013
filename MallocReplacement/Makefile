CXX = c++
CFLAGS = -std=c++17
OBJS = myMalloc.o hashTable.o main.o

all:
	make malloc

malloc: $(OBJS)
	$(CXX) $(OBJS) -o malloc

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

myMalloc.o: MyMalloc.cpp MyMalloc.h
	$(CXX) $(CFLAGS) -c MyMalloc.cpp

hashTable.o: HashTable.cpp HashTable.h
	$(CXX) $(CFLAGS) -c HashTable.cpp

.PHONY:clean
clean:
	rm -rf *.o *.out malloc