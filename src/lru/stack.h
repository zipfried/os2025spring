#ifndef STACK_H
#define STACK_H

void stack_init(int capacity);

int stack_is_empty();

int stack_is_full();

int stack_push(int value);

int stack_pop();

int stack_pop_bottom();

int stack_find(int value);

int stack_move_to_top(int index);

void stack_display();

#endif // STACK_H
