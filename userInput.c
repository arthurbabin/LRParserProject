#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void getUserInput(char* buf){
    fgets(buf, 256, stdin);
    sscanf(buf, "%hhu",buf);
}

void dispUserInput(char* buf){
    printf("User Input : %s = [",buf);
    for(int i=0;i<256;i+=1){
        if(buf[i]==10){
            i=256;
            printf(" \\n]\n");
        } else {
            printf("%4i,",buf[i]);
        }
    }
}

int main(){
    char user_input[256];
    getUserInput(user_input);
    dispUserInput(user_input);
}