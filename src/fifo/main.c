#include "queue.h"

#include <stddef.h>
#include <stdio.h>

int main() {
  const int FRAME_COUNT = 3;
  queue_t queue;
  queue_init(&queue, FRAME_COUNT);

  const int TEST_DATA[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3,
                           0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
  const size_t TOTAL_COUNT = sizeof(TEST_DATA) / sizeof(int);

  size_t err_count = 0;

  for (size_t i = 0; i < TOTAL_COUNT; i++) {
    int page = TEST_DATA[i];
    int find = queue_find(&queue, page);
    if (find == -1) {
      printf("miss %d\n", page);
      err_count++;
      if (!queue_is_full(&queue)) {
        queue_push(&queue, page);
      } else {
        queue_pop(&queue);
        queue_push(&queue, page);
      }
    }
    queue_display(&queue);
  }
  printf("%f\n", 100.0 * err_count / TOTAL_COUNT);
}
