//
//  sayHello.cpp
//  
//
//  Created by Rason Hung on 1/27/23.
//

#include <stdio.h>
#include <string.h>

extern "C" {
    void sayHello();
    void myPuts(const char* s, int len);
}


int main(int argc, char *argv[]){
    sayHello();
    const char* str = "myPuts output\n";
    myPuts(str,strlen(str));
    return 0;
}
