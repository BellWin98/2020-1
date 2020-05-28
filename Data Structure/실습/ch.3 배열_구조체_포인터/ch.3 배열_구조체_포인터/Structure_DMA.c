#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dynamic {
	int num;
	char name[20];
}Dynamic;
int main() {
	Dynamic *input;
	input = (Dynamic *)malloc(sizeof(Dynamic));
	input->num = 23;
	strcpy(input->name, "Han JongSeung");
	printf("my name is %s\nmy age is %d\n", input->name, input->num);
	free(input);
	return 0;
}