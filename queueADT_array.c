#include <stdio.h>
#include <stdlib.h>
#include "queueADT.h"

#define INIT_CAPACITY 100

struct queue_type {
	Item* contents; // �迭
	int front;
	int rear;
	int size; // ����� �������� ����
	int capacity; // �迭 contents�� ũ��
};

void termitnate(const char* message) {
	printf("%s\n", message);
	exit(1);
}

int get_size(Queue q) {
	return q->size;
}

Queue create() {
	Queue q = (Queue)malloc(sizeof(struct queue_type)); // ť �Ҵ�
	if (q == NULL) {
		terminate("Error in create: queue could not be created");
	}
	q->contents = (Item*)malloc(INIT_CAPACITY * sizeof(Item)); // �迭 �Ҵ�
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
	q->rear = (q->rear + 1) % q->capacity; // rear�� �迭�� �� �������� ��츦 �ذ�
	q->contents[q->rear] = i;
	q->size++;
}

Item dequeue(Queue q) {
	if (is_empty(q)) {
		terminate("Error in dequeue: queue is empty.");
	}
	Item result = q->contents[q->front];
	q->front = (q->front + 1) % q->capacity; // front�� �迭�� �� �������� ��츦 �ذ�
	q->size--;

	return result; // q->contents[q->front-1] ���� ������ ������ �ʵ��� ����!
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

	int j = q->front;  // front ���� ����
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