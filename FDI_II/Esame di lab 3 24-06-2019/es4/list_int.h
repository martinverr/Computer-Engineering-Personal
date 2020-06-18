/** @file
In questo file sono definite le primitive delle liste disponibili 
per l'esame del 24/06/2019
*/
#ifndef LIST_INT_H_
#define LIST_INT_H_

#include <stdbool.h>
#include <stdlib.h>

typedef int element;

typedef struct list_element {
    element value;
    struct list_element *next;
} item;

typedef item* list;

/** @brief La funzione Emptylist ritorna una lista vuota (NULL).
 
@returns Lista vuota (NULL).

*/
list EmptyList(void);


/** @brief La funzione Cons aggiunge un nuovo elemento in testa ad una lista e ritorna la lista modificata.

@param e Elemento da aggiugnere.
@param l Lista da aggiornare con il nuovo elemento, puo' essere una lista vuota (NULL).

@returns Lista aggiornata.
*/
list Cons(const element *e, list l);

/** @brief Controlla se una lista e' vuota.

@param l Lista da controllare.

@returns true se la lista e' vuota, false altrimenti.
*/
bool IsEmpty(list l);

/** @brief Ritorna l'elemento in testa ad una lista senza eliminarlo.

@param l Lista da cui estrarre l'elemento in testa. Non puo' essere una lista vuota.

@returns Elemento in testa alla lista.
*/
element Head(list l);

/** @brief Ritorna una lista privata dell'elemento in testa. N.B. la funzione non dealloca la memoria occupata dall'elemento head della lista.

@param l Lista da cui eliminare l'elemento in testa. Non puo' essere una lista vuota.

@return Lista ottenuta dopo l'eliminazione dell'elemento in testa. Puo' essere una lista vuota.
*/
list Tail(list l);

/** @brief Ritorna una copia di un elemento e.

@param e Elemento da copiare.

@returns Copia dell'elemento.
*/
element Copy(const element *e);

/** @brief Aggiunge un elemento in coda ad una lista (anche vuota) e 
ritorna la lista risultante.

@param l Lista a cui aggiungere l'elemento. Può essere una lista vuota (NULL).
@param e Elemento da aggiungere alla lista l.

@returns Lista ottenuta aggiungendo l'elemento e alla lista l.
*/
list InsertBack(list l, const element *e);

/** @brief Data la testa di una lista, libera la memoria occupata dai suoi elementi.

@param l Testa della lista di cui liberare la memoria.
*/
void FreeList(list l);

#endif // !LIST_INT_H_

