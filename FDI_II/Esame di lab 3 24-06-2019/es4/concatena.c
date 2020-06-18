#include "list_int.h"

list lastItem(list l) {
	while (l->next) {
		l = l->next;
	}
	return l;
}

list Concatena(list l1, list l2, list l3) {
	if(l1) 
		lastItem(l1)->next = l2;
	else l1 = l2;
	
	if(l1) 
		lastItem(l1)->next = l3;
	else l1 = l3;

	/*
	se non ci fossero liste vuote basterebbe:
	lastItem(l1)->next = l2;
	lastItem(l2)->next = l3;
	return l1;
	*/
	return l1;
}