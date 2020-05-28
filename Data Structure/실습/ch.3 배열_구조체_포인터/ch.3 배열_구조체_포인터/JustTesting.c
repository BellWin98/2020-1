#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct test {
	int i;
	char str[20];
};
int main(void) {
	struct test *p;
	p = (struct test*)malloc(sizeof(struct test));
	if (p == NULL) {
		printf("memory error\n");
		return;
	}
	p->i = 100;
	strcpy(p->str, "just testing");
	printf("i = %d, str = %s\n", p->i, p->str);
	free(p);
	return 0;
}
