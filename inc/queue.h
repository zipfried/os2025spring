#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_t {
  int *buf;
  int capacity;
  int head;
  int tail;
  int is_same_cycle;
} queue_t;

int queue_init(queue_t *queue, int capacity);

int queue_drop(queue_t *queue);

int queue_is_empty(queue_t *queue);

int queue_is_full(queue_t *queue);

int queue_push(queue_t *queue, int data);

int queue_pop(queue_t *queue);

int queue_find(queue_t *queue, int data);

void queue_display(queue_t *queue);

#endif // QUEUE_H
