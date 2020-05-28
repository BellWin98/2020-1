//#pragma warning(disable: 4996)
//#include <stdio.h>
//#include <stdlib.h>
//#define MAX_QUEUE_SIZE 5
//
//typedef int element;
//typedef struct {
//	element front, rear;
//	element data[MAX_QUEUE_SIZE];
//} QueueType;
//
//// 오류함수
//void error(char *message);
//void init_queue(QueueType *q);
//int is_full(QueueType *q);
//int is_empty(QueueType *q);
//void enqueue(QueueType *q, int item);
//int dequeue(QueueType *q);
//int fibonacci(QueueType* q, int n);
//
//int main() {
//
//	QueueType *q;
//	q = (QueueType *)malloc(sizeof(QueueType));
//	init_queue(q);
//	int n = 3;
//	printf("%d\n", fibonacci(q, n));
//
//	free(q);
//
//	return 0;
//}
//
//void error(char *message) {
//	fprintf(stderr, "%s\n", message);
//	exit(1); // 비정상종료, exit(0)은 정상종료
//}
//
//void init_queue(QueueType *q) {
//	q->front = 0;
//	q->rear = 0;
//}
//
//
//int is_full(QueueType *q) {
//	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
//}
//
//int is_empty(QueueType *q) {
//	return (q->front == q->rear);
//}
//
//void enqueue(QueueType *q, int item) {
//	if (is_full(q)) {
//		error("Queue is full.");
//		return;
//	}
//
//	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
//	q->data[q->rear] = item;
//}
//
//element dequeue(QueueType *q) {
//	if (is_empty(q)) {
//		error("Queue is empty.");
//		return -1;
//	}
//	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
//	return q->data[q->front];
//}
//
//int fibonacci(QueueType* q, int n) {
//	
//	if (n < 2) {
//		return n;
//	}
//
//	enqueue(q, 0);
//	enqueue(q, 1);
//	int i = 2;
//	while (i <= n) {
//		element e1 = dequeue(q);
//		element e2 = dequeue(q);
//		element e3 = e1 + e2;
//		enqueue(q, e2);
//		enqueue(q, e3);
//		i++;
//	}
//	return dequeue(q);
//}
//
//
