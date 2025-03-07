#include "queue.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  const size_t TOTAL = 512;
  const size_t PAGE = 16;

  FILE *res = NULL;
  res = fopen("fifo.txt", "w");

  for (size_t i = 0; i < 10; i++) {
    // generate test data
    srand((unsigned)i);
    int *requests = (int *)malloc(TOTAL * sizeof(int));
    for (size_t j = 0; j < TOTAL; j++) {
      requests[j] = rand() % 32;
    }

    for (size_t capacity = 1; capacity <= PAGE; capacity++) {
      queue_t queue;
      queue_init(&queue, capacity);
      size_t err = 0;

      for (size_t j = 0; j < TOTAL; j++) {
        int page = requests[j];
        int find = queue_find(&queue, page);
        if (find == -1) {
          err++;
          if (!queue_is_full(&queue)) {
            queue_push(&queue, page);
          } else {
            queue_pop(&queue);
            queue_push(&queue, page);
          }
        }
      }
      fprintf(res, "%.2f,", 100.0 * err / TOTAL);
    }
    fprintf(res, "\n");
  }

  fclose(res);
  return 0;
}
