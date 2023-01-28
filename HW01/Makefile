mySyscallProgram: main.o myAsm.o
	clang++ main.o myAsm.o -o mySyscallProgram

main.o: main.cpp
	clang++ -c main.cpp

myAsm.o: myAsm.s
	nasm -felf64 myAsm.s

.PHONY: clean
clean:
	rm *.o mySyscallProgram