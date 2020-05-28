#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {
	element front;
	element rear;
	element data[MAX_QUEUE_SIZE];
} QueueType;

// �����Լ�
void error(char *message);
void init_queue(QueueType *q);
void queue_print(QueueType *q);
int is_full(QueueType *q);
int is_empty(QueueType *q);
void enqueue(QueueType *q, int item);
int dequeue(QueueType *q);
int get_count(QueueType *q);

int main() {

	QueueType *queue;
	queue = (QueueType *)malloc(sizeof(QueueType));
	int element;

	init_queue(queue);
	printf("--������ �߰� �ܰ�--\n");
	while (!is_full(queue)) {
		printf("������ �Է��Ͻÿ�: ");
		scanf("%d", &element);
		enqueue(queue, element);
		queue_print(queue);
		printf("ť�� �����ϴ� ����� ����: %d\n", get_count(queue));
	}
	printf("Queue is full\n\n");

	printf("--������ ���� �ܰ�--\n");
	while (!is_empty(queue)) {
		element = dequeue(queue);
		printf("������ ����: %d \n", element);
		queue_print(queue);
		printf("ť�� �����ϴ� ����� ����: %d\n", get_count(queue));
	}
	printf("Queue is empty\n");

	free(queue);
	return 0;
}

void error(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1); // ����������, exit(0)�� ��������
}

void init_queue(QueueType *q) {
	q->front = 0;
	q->rear = 0;
}

void queue_print(QueueType *q) {

	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			printf("%d | ", q->data[i]);
			if (i == q->rear) {
				break;
			}
		} while (i != q->front);
	}
	printf("\n");
}

int is_full(QueueType *q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_empty(QueueType *q) {
	return (q->front == q->rear);
}

void enqueue(QueueType *q, int item) {
	if (is_full(q)) {
		error("Queue is full.");
		return;
	}
	
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType *q) {
	if (is_empty(q)) {
		error("Queue is empty.");
		return -1;
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

int get_count(QueueType *q) {

	if (q->front <= q->rear) {
		return q->rear - q->front;
	}
	else {
		return MAX_QUEUE_SIZE - (q->front - q->rear);
	}

}


