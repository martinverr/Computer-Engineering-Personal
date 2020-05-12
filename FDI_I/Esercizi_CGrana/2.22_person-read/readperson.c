#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct person { char name[256]; unsigned int age; };

void person_read(FILE *f, struct person *pp) {
	fscanf(f, "%s", &(pp->name));
	fscanf(f, "%d", &(pp->age));
}

int main(void)
{
	FILE *f1 = fopen("person1.txt", "r");
	FILE *f2 = fopen("person2.txt", "r");
	struct person *person1 = malloc(sizeof(struct person));
	struct person *person2 = malloc(sizeof(struct person));
	
	person_read(f1, person1);
	//person_read(f2, person2);

	return 0;
}
