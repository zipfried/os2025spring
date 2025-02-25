#include "stack.h"

#include <stddef.h>
#include <stdio.h>

#define VERBOSE

int main() {
  const int FRAME_COUNT = 3;
  stack_init(FRAME_COUNT);

  const int TEST_DATA[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1,
                           7, 0, 1, 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1,
                           2, 0, 1, 7, 0, 1, 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0,
                           3, 2, 1, 2, 0, 1, 7, 0, 1, 7, 0, 1, 2, 0, 3, 0, 4,
                           2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1, 7, 0, 1, 2, 0,
                           3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
  const size_t TOTAL_COUNT = sizeof(TEST_DATA) / sizeof(int);

  size_t err_count = 0;

  for (size_t i = 0; i < TOTAL_COUNT; i++) {
    int page = TEST_DATA[i];
    int find = stack_find(page);
    if (find == -1) {
      err_count++;
      if (!stack_is_full()) {
        stack_push(page);
      } else {
        stack_pop_bottom();
        stack_push(page);
      }
    } else {
      stack_move_to_top(find);
    }
#ifdef VERBOSE
    stack_display();
#endif
  }
  printf("%f\n", 100.0 * err_count / TOTAL_COUNT);
}
