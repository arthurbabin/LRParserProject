#include <stdlib.h>
#include <stdio.h>

/* Structure de liste */

typedef double value;

typedef struct Node {
    value v;
    struct Node* next;
} *List;

/*
@requires: nothing
@assigns: nothing
@ensures: retourne la liste vide
*/
List create_empty() {
    return NULL;
}

/*
@requires: nothing
@assigns: nothing
@ensures: retourne la liste vide
*/
int is_empty(List l) {
    return l == NULL;
}

List make(List l, value e){
    List new = malloc(sizeof(struct Node));
    new->v = e;
    new->next = l;
    return new;
}

void affichageList(List l){
    while(!is_empty(l)){
        printf("[%.2f] -> ",l->v);
        l = l->next;
    }
    printf("[]\n\n");
}

void half_insert(List l){
    if(!is_empty(l)&&!is_empty(l->next)){
        List new = malloc(sizeof(struct Node));
        new->v = ((l->v)+(l->next->v))/2;
        new->next = l->next;
        l->next = new;
        half_insert(l->next->next);
    }
}

List range2(int n){
    List l = create_empty();
    int i = n;
    while(i>=2){
        l = make(l,i);
        i--;
    }
    return l;
}

void insert(List *l, value e) {
    if (NULL == *l) {
        *l = make(NULL,e);
    } else {
        if (e <= (*l)->v) {
            *l = make(*l, e);
        } else {
            List curr = *l;
            while (curr->next != NULL && curr->next->v < e) {
                curr = curr->next;
            }
            curr->next = make(curr->next, e);
        }
    }
}

void insertion_sort(List *l){
    List m = *l;
    List res = create_empty();
    while(!is_empty(m)){
        insert(&res,m->v);
        m = m->next;
    }
    return res;
}

int main(){
    printf("\n");
    List a = range2(5);
    affichageList(a);
    half_insert(a);
    affichageList(a);

    List b = range2(5);
    insert(&b,6);
    affichageList(b);

    List c = create_empty();
    c = make(c,5);
    c = make(c,6);
    c = make(c,3);
    affichageList(insertion_sort(c));


    return 0;
}