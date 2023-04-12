#include <stdio.h>
#include <stdlib.h>
#include "queueADT.h"

#define INIT_CAPACITY 100

struct queue_type {
	Item* contents; // 배열
	int front;
	int rear;
	int size; // 저장된 데이터의 개수
	int capacity; // 배열 contents의 크기
};

void termitnate(const char* message) {
	printf("%s\n", message);
	exit(1);
}

int get_size(Queue q) {
	return q->size;
}

Queue create() {
	Queue q = (Queue)malloc(sizeof(struct queue_type)); // 큐 할당
	if (q == NULL) {
		terminate("Error in create: queue could not be created");
	}
	q->contents = (Item*)malloc(INIT_CAPACITY * sizeof(Item)); // 배열 할당
	if (q->contents == NULL) {
		free(q);
		terminate("Error in create: queue could not be created");
	}
	q->front = 0;
	q->rear = -1;
	q->size = 0;
	q->capacity = INIT_CAPACITY;
	return q;
}

void destroy(Queue q) {
	free(q->contents);
	free(q);
}

void make_empty(Queue q) {
	q->front = 0;
	q->rear = -1;
	q->size = 0;
}

bool is_empty(Queue q) {
	return q->size == 0;
}

bool is_full(Queue q) {
	return q->size == q->capacity;
}

void enqueue(Queue q, Item i) {
	if (is_full(q)) {
		reallocate(q);
	}
	q->rear = (q->rear + 1) % q->capacity; // rear가 배열의 맨 마지막인 경우를 해결
	q->contents[q->rear] = i;
	q->size++;
}

Item dequeue(Queue q) {
	if (is_empty(q)) {
		terminate("Error in dequeue: queue is empty.");
	}
	Item result = q->contents[q->front];
	q->front = (q->front + 1) % q->capacity; // front가 배열의 맨 마지막인 경우를 해결
	q->size--;

	return result; // q->contents[q->front-1] 같은 오류를 범하지 않도록 주의!
}

Item peek(Queue q) {
	if (is_empty(q)) {
		terminate("Error in peek: queue is empty.");
	}
	return q->contents[q->front];
}

void reallocate(Queue q) {
	Item* tmp = (Item *)malloc(2 * q->capacity * sizeof(Item));
	if (tmp == NULL) {
		terminate("Error in create: queue could not be expanded");
	}

	int j = q->front;  // front 부터 복사
	for (int i = 0; i < q->size; i++) {
		tmp[i] = q->contents[j];
		j = (j + 1) % q->capacity;
	}

	free(q->contents);
	q->front = 0;
	q->rear = q->size - 1;
	q->contents = tmp;
	q->capacity *= 2;
}