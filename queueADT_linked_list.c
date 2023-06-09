#include "queueADT.h"
#include <stdio.h>
#include <stdlib.h>

struct node {
	Item data;
	struct node* next;
};

struct queue_type {
	struct node* front;
	struct node* rear;
	int size;
};

void terminate(const char* message) {
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

int get_size(Queue q) {
	return q->size;
}

Queue create() {
	Queue q = (Queue)malloc(sizeof(struct queue_type));
	if (q == NULL) {
		terminate("Error in create: queue could not be created");
	}
	q->front = NULL;
	q->rear = NULL;
	q->size = 0;
	return q;
}

void destroy(Queue q) {
	make_empty(q);
	free(q);
}

void make_empty(Queue q) {
	while (!is_empty(q)) {
		dequeue(q);
	}
	q->size = 0;
}

bool is_empty(Queue q) {
	return q->front == NULL; // or return q->size == 0;
}

void enqueue(Queue q, Item i) {
	struct node* new_node = (struct node *)malloc(sizeof(struct node));
	if (new_node == NULL) {
		terminate("Error in push: queue is full.");
	}

	new_node->data = i;
	new_node->next = NULL; // 연결리스트의 맨 뒤에 삽입하기 때문
	if (q->front == NULL) {
		q->front = new_node;
		q->rear = new_node;
	}
	else {
		q->rear->next = new_node;
		q->rear = new_node;
	}
	q->size++;
}

Item dequeue(Queue q) {
	struct node* old_front;
	Item i;

	if (is_empty(q)) {
		terminate("Error in dequeue: queue is empty.");
	}

	old_front = q->front;
	i = old_front->data;
	q->front = old_front->next;
	if (q->front == NULL) { // 저장된 노드가 1개인 경우
		q->rear = NULL;
	}

	free(old_front);
	q->size--;
	
	return i;
}

Item peek(Queue q) {
	if (is_empty(q)) {
		terminate("Error in peek: queue is empty.");
	}
	return q->front->data;
}