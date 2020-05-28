#include <stdio.h>

void Insert_Value(int array[], int *loc, int *val, int *length);

int main() {

	int arr[5] = { 15, 23, 54, 34, 47};
	int location = 4;
	int value = 17;
	int len = sizeof(arr) / sizeof(int);
	printf("before insert value = ");
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	Insert_Value(arr, &location, &value, &len);
	printf("after insert value = ");
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;

}

void Insert_Value(int array[], int *loc, int *val, int *length) {

	for (int i = *length; i >= *loc; i--) {
		array[i + 1] = array[i];
	}
	array[*loc] = *val;
	*length++;
}