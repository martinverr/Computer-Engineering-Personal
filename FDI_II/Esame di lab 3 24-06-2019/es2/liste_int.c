#include "list_int.h"
#include <stdio.h>

list EmptyList(void)
{
    return NULL;
}

list Cons(const element *e, list l) 
{
    list t;
    t = malloc(sizeof(item));
    t->value = Copy(e);
    t->next = l;
    return t;
}

bool IsEmpty(list l) {
    return (l == NULL);
}

element Head(list l) {
    if (IsEmpty(l)) {
        printf("ERROR: Alla funzione 'Head()' è stata passata una lista vuota (NULL pointer).\n");
        abort();
    }
    else {
        return l->value;
    }
}

list Tail(list l) {
    if (IsEmpty(l)) {
        printf("ERROR: Alla funzione 'Tail()' è stata passata una lista vuota (NULL pointer).\n");
        abort();
    }
    else {
        return l->next;
    }
}

element Copy(const element *e) {
    element el;
    el = *e;
    return el;
}

list InsertBack(list l, const element *e)
{
    // Costruisco un item per il nuovo elemento
    list n = Cons(e, EmptyList());

    // Se la lista l è vuota, n è quello che la
    // funzione deve ritornare
    if (IsEmpty(l)) {
        return n;
    }

    // Scorro tutti gli elementi (item) della 
    // lista fino ad arrivare all'ultimo
    list tmp = l;
    while (!IsEmpty(Tail(tmp))) {
        tmp = Tail(tmp);
    }

    // Faccio puntare l'ultimo elemento (item) 
    // della lista a quello nuovo e ritorno la
    // lista risultante
    tmp->next = n;
    return l;
}

void FreeList(list l) {
    while (!IsEmpty(l)) {
        list tmp = l;
        l = l->next;
        free(tmp);
    }
}
