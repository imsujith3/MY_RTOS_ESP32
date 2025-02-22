#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#define MAX_TASKS 2
#define STACK_SIZE 2048

typedef struct {
    void (*task_function)();
    uint8_t stack[STACK_SIZE];
    void *stack_pointer;
} tcb_t;

void init_tasks();

#endif
