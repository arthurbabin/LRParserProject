#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct Step {
    int s;
    struct Step* next;
} *Stack;

Stack create_empty_stack() {
    return NULL;
}

int is_empty(Stack l) {
    return l == NULL;
}

Stack stack(Stack l, int e){
    Stack new = malloc(sizeof(struct Step));
    new->s = e;
    new->next = l;
    return new;
}

int pop(Stack l){
    int res = l->s;
    l = l->next;
    return res;
}

void printStack(Stack l){
    while(!is_empty(l)){
        printf("[%i] -> ",l->s);
        l = l->next;
    }
    printf("[]\n\n");
}

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

void getGroupMarkers(int* nb_states, int* start_action, int* start1_reduce, int* start2_reduce, int* start_shift, int* start_connect, unsigned char buffer[]){
    int i = 2;
    *nb_states = 0;
    while(buffer[i]!=10){
        *nb_states = *nb_states*10 + ( (int)buffer[i] -48);
        i+=1;
    }
    *start_action = ++i;
    i += 128 * (*nb_states) + 1;
    *start1_reduce = i;
    *start2_reduce = *start1_reduce + *nb_states + 1;
    *start_shift = *start2_reduce + *nb_states + 1;
    i = *start_shift;
    while(buffer[i]!=173 && buffer[i+1]!=173 && buffer[i+2]!=173){
        i+=3;
    }
    i += 3;
    *start_connect = i;
}

int action(int s, int c, int start, unsigned char buffer[]){
    int i =  start + c + 128 * s ;
    return (int) buffer[i];
}

int getNumberOfStates(unsigned char buffer[]){
    int i = 2;
    int nb = 0;
    while(buffer[i]!=10){
        nb = nb*10 + ( (int)buffer[i] -48);
        i+=1;
    }
    return nb;
}

void afficherAut(unsigned char buffer[], int size){
    int test = 0;
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
        } else {
            printf("%i ", convertBase10to(buffer[i],base));
            test+=1;
        }
    }
}

// unsigned char* getInput(){
//     unsigned char user_input[256];
//     fgets(user_input,256,stdin);
//     sscanf(user_input,"%s\n");
//     return user_input;
// }


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
        afficherAut(buffer,size);
        printf("\n Nombre d'états : %i\n",getNumberOfStates(buffer));
        int nb_states, start_action, start1_reduce, start2_reduce, start_shift, start_connect;
        getGroupMarkers(&nb_states, &start_action, &start1_reduce, &start2_reduce, &start_shift, &start_connect, buffer);
        printf("%i, %i, %i, %i, %i, %i\n ", nb_states, start_action, start1_reduce, start2_reduce, start_shift, start_connect);
        printf("%i\n",action(0,10,start_action,buffer));
        // printf("%s\n",getInput());
    }

    return 0;
}