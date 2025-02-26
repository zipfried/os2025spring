#include "queue.h"

#include <stdlib.h>
#include <string.h>

int queue_init(queue_t *queue, int capacity) {
  memset(queue, 0, sizeof(*queue));
  queue->buf = (int *)malloc(capacity * sizeof(int));
  if (queue->buf == NULL) {
    return -1;
  }

  queue->capacity = capacity;
  queue->head = 0;
  queue->tail = 0;
  queue->is_same_cycle = 1;

  return 0;
}

int queue_drop(queue_t *queue) {
  free(queue->buf);
  queue->buf = NULL;

  return 0;
}

int queue_is_empty(queue_t *queue) {
  return queue->head == queue->tail && queue->is_same_cycle;
}

int queue_is_full(queue_t *queue) {
  return queue->head == queue->tail && !queue->is_same_cycle;
}

int queue_push(queue_t *queue, int data) {
  if (queue_is_full(queue)) {
    return -1;
  }

  queue->buf[queue->tail] = data;
  queue->tail = (queue->tail + 1) % queue->capacity;
  queue->is_same_cycle = !(queue->tail == 0);

  return 0;
}

int queue_pop(queue_t *queue) {
  if (queue_is_empty(queue)) {
    return -1;
  }

  int data = queue->buf[queue->head];
  queue->head = (queue->head + 1) % queue->capacity;
  queue->is_same_cycle = queue->head == 0;

  return data;
}
