#include "stack.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  const size_t TOTAL = 512;
  const size_t PAGE = 16;

  FILE *res = NULL;
  res = fopen("lru.txt", "w");

  for (size_t i = 0; i < 10; i++) {
    // generate test data
    srand((unsigned)i);
    int *requests = (int *)malloc(TOTAL * sizeof(int));
    for (size_t j = 0; j < TOTAL; j++) {
      requests[j] = rand() % PAGE;
    }

    for (size_t capacity = 1; capacity <= PAGE; capacity++) {
      stack_init(capacity);
      size_t err = 0;

      for (size_t j = 0; j < TOTAL; j++) {
        int page = requests[j];
        int find = stack_find(page);
        if (find == -1) {
          err++;
          if (!stack_is_full()) {
            stack_push(page);
          } else {
            stack_pop_bottom();
            stack_push(page);
          }
        } else {
          stack_move_to_top(find);
        }
      }
      fprintf(res, "%.2f,", 100.0 * err / TOTAL);
    }
    fprintf(res, "\n");
  }

  fclose(res);

  return 0;
}
