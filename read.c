#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fin;
    int character;
    fin=fopen("LR1/arith.aut", "r");
    while((character=fgetc(fin))!=EOF){
        putchar(c); // It displays weird characters in the file
    }
    fclose(fin);
    return 0;
}