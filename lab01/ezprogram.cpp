#include <cstdio>

template <typename T>
T add(T a, T b){
    return a + b;
}

int main(int argc, char *argv[]){
    printf("%d\n", add(1,3));
    return 0;
}
