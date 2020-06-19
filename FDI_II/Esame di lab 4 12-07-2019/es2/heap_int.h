/** @file
 Documentazione heap esame 12/07/2019
*/
#ifndef HEAP_INT_H_
#define HEAP_INT_H_

#include <stdbool.h>
#include <stdlib.h>

typedef int element;

/** @brief Ritorna l'indice del figlio sinistro 

La funzione Left() prende in input l'indice di un nodo
e calcola l'indice del figlio suo figlio sinistro

@param i Indice di un nodo

@return Indice del figlio sinistro del nodo i
*/
int Left(int i);

/** @brief Ritorna l'indice del figlio destro

La funzione Right() prende in input l'indice di un nodo
e calcola l'indice del figlio suo figlio destro

@param i Indice di un nodo

@return Indice del figlio destro del nodo i
*/
int Right(int i);

/** @brief Ritorna l'indice del padre

La funzione Parent() prende in input l'indice di un nodo
e calcola l'indice del nodo padre

@param i Indice di un nodo

@return Indice del nodo padre di i
*/
int Parent(int i);

/** @brief Confronta due elementi della coda heap

La funzione Compare() prende in input due element
della coda heap e ritorna -1 se il primo e' minore
del secondo, +1 se il primo e' maggiore del secondo
e 0 se sono uguali.

@param e1 Puntatore al primo elemento da confrontare.
@param e2 Puntatore al secondo elemento da confrontare.

@return -1, 0, +1 a seconda del risultato del confronto
*/
int Compare(const element *e1, const element *e2);

/** @brief Scambia due elementi della coda heap

La funzione Swap() prende in input due element
della coda heap e li scambia.

@param e1 Puntatore al primo elemento da scambiare.
@param e2 Puntatore al secondo elemento da scambiare.

@return
*/
void Swap(element *e1, element *e2);

/** @brief Dato l'indice di un nodo i, lo scambia con il padre
finche' il nodo non soddisfa l'ordinamento (max)heap

La funzione MoveUpMaxHeap() prende in input l'indice di un nodo i e 
una coda (max)heap e scambia il nodo i con il padre fino a quando
la coda (max)heap non soddisfa l'ordinamento. 

@param h Coda (max)heap.
@param i Indice del nodo su cui applicare la MoveUpMaxHeap.

@return
*/
void MoveUpMaxHeap(element *h, int i);

/** @brief Dato l'indice di un nodo i, lo scambia con il figlio
maggiore fino a che il nodo non soddisfa l'ordinamento (max)heap

La funzione MoveDownMaxHeap() prende in input l'indice di un nodo 
i e una coda (max)heap e scambia il nodo i con il figlio maggiore
fino a quando la coda (max)heap non soddisfa l'ordinamento.

@param h Coda (max)heap.
@param i Indice del nodo su cui applicare la MoveDownMaxHeap.

@return
*/
void MoveDownMaxHeap(element *h, int i);

/** @brief Crea e ritorna una (max/min)heap vuota.

Il primo elemento dell'array che implementa la coda
heap viene utilizzato per memorizzare la dimensione
della coda stessa.

@return
*/
element *CreateHeap();

/** @brief Libera la memoria occupata da un coda heap

@param h Coda heap

@return
*/
void FreeHeap(element *h);

/** @brief Trasforma un vettore qualsiasi v in una coda (max)Heap

La funzione HeapifyMaxHeap() prende in input un vettore v e la sua
dimensione v_size e crea una coda (max)heap contenente i dati di v.
La heap di output avra' dimensione v_size + 1 per poter contenere
il campo "size" della heap.

@param v Vettore di element.
@param v_size Numero di elementi contenuti in v.

@return Coda (max)heap.
*/
element* HeapifyMaxHeap(element *v, size_t v_size);

#endif // !HEAP_INT_H_