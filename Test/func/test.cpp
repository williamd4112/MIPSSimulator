#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

int main(){
    FILE *fp = fopen("iimage.bin", "rb");
    if(fp == NULL) {
        printf("error\n");
        exit(1);
    }

    char byte;
    int i = 0;
    while((byte = fgetc(fp)) != EOF){
        printf("0x%x ",byte);
        if(i++ == 4) {
            putchar('\n');
            i = 0;
        }

    }

    return 0;
}
