#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int convertBase10to(int x, int b){
    int res = 0;
    int i = 1;
    while(x!=0){
        res +=(x%b) * i;
        x = x/b;
        i = i * 10;
    }
    return res;
}

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr,"Error usage: %s path_to_file",argv[0]);
        return 1;
    }
    struct stat properties;
    int verif = lstat(argv[1],&properties);
    if(verif==-1){
        perror("lstat");
        return 1;
    }
    off_t size = properties.st_size;
    if (size > 0){
        FILE *fin; 
        fin=fopen(argv[1], "rb");
        unsigned char buffer[size];
        if (buffer==NULL){
            perror("malloc");
            return 1;
        }

        fread(buffer,sizeof(buffer),1,fin);
        
        int test = 0;
        int test2;
        int countenter = 0;
        int a,b,c;
        int base = 10;
        for(int i = 0; i<size; i++) {
            if (buffer[i]==10 && countenter<4){
                countenter+=1;
                printf("\n => %i caractères \n\n",test);
                test = 0;
            } else if (countenter>=4){
                a = buffer[i];
                b = buffer[i+1];
                c = buffer[i+2];
                if (a==173 && b==173 && c==173){
                    printf("%i %i %i \n", convertBase10to(a,base),convertBase10to(b,base),convertBase10to(c,base));
                    printf("\n => bloc de trois \n\n");
                } else {
                    printf("%i %i %i \n", convertBase10to(a,base),convertBase10to(b,base),convertBase10to(c,base));
                }
                i+=2;
                test+=1;
                test2 = buffer[i];
            } else {
                printf("%i ", convertBase10to(buffer[i],base));
                test+=1;
            }
        }
        printf("\ntest2 :  %i", test2);
    }

    return 0;
}