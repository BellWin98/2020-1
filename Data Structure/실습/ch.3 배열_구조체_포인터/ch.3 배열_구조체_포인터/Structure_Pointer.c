#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct studentTag {
	char name[10]; // packing 2 more bytes 
	int age; // 4 bytes
	double gpa; // 8 bytes
} student;

int main() {
	student *p;
	p = (student *)malloc(2*sizeof(student)); // allocates 24 bytes *2
	if (p == NULL) {
		fprintf(stderr, "메모리가 부족해서 할당할 수 없습니다.\n");
		exit(1);
	}
	strcpy(p->name, "Han");
	p->age = 23;
	p->gpa = 4.1;
	strcpy((p + 1)->name, "John");
	(p + 1)->age = 21; // p[1]->age
	(p + 1)->gpa = 3.5; // p[1]->gpa
	printf("name1: %s, age1: %d, gpa1: %.1f\n", p->name, p->age, p->gpa);
	printf("name2: %s, age2: %d, gpa2: %.1f\n", (p+1)->name, (p + 1)->age, (p + 1)->gpa);
	return 0;

}