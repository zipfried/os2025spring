#include "stack.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int *g_stack_data = NULL;
static int g_stack_capacity = 0;
static int g_stack_top = 0;

void stack_init(int capacity) {
  // We do not consider cases where the capacity is zero.
  assert(capacity > 0);

  // If the stack has been initialized before, free the memory.
  // There is only one global stack since this is just for testing.
  if (g_stack_data) {
    free(g_stack_data);
  }
  g_stack_data = (int *)malloc(capacity * sizeof(int));
  g_stack_capacity = capacity;
  g_stack_top = 0;
}

int stack_is_empty() { return g_stack_top <= 0; }

int stack_is_full() { return g_stack_top >= g_stack_capacity; }

int stack_push(int value) {
  if (stack_is_full()) {
    return -1; // Full.
  }
  g_stack_data[g_stack_top] = value;
  return g_stack_top++; // Return the index of the pushed data.
}

int stack_pop() {
  if (stack_is_empty()) {
    return -1;
  }
  g_stack_top--;
  return g_stack_data[g_stack_top];
}

int stack_pop_bottom() {
  if (stack_is_empty()) {
    return -1;
  }
  int value = g_stack_data[0];
  for (size_t i = 0; i < g_stack_top - 1; i++) {
    g_stack_data[i] = g_stack_data[i + 1];
  }
  g_stack_top--;
  return value;
}

int stack_find(int value) {
  for (size_t i = 0; i < g_stack_top; i++) {
    if (g_stack_data[i] == value) {
      return i;
    }
  }
  return -1;
}

int stack_move_to_top(int index) {
  if (index < 0 || index >= g_stack_top) {
    return -1;
  }
  int value = g_stack_data[index];
  for (size_t i = index; i < g_stack_top - 1; i++) {
    g_stack_data[i] = g_stack_data[i + 1];
  }
  g_stack_data[g_stack_top - 1] = value;
  return g_stack_top - 1;
}

void stack_display() {
  for (size_t i = 0; i < g_stack_top; i++) {
    printf("%d ", g_stack_data[i]);
  }
  for (size_t i = g_stack_top; i < g_stack_capacity; i++) {
    printf("_ ");
  }
  printf("\n");
}
