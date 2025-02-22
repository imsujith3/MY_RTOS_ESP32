#include "task.h"
#include "esp_log.h"
#include "string.h"

tcb_t task_list[MAX_TASKS];  // Task control blocks
int current_task = 0;        // Track the running task

void task1(void) {
    while (1) {
        ESP_LOGI("Task1", "Executing Task 1...");
        for (volatile int i = 0; i < 1000000; i++); // Simulated workload
        ESP_LOGI("Task1", "Task 1 completed.");
    }
}
void task2() {
    ESP_LOGI("Task2", "Executing Task 2...");

    // Add debug prints
    ESP_EARLY_LOGI("Task2", "Task2 stack pointer: %p", &task_list[1].stack_pointer);

    for (volatile int i = 0; i < 1000000; i++); // Simulated workload

    ESP_LOGI("Task2", "Task 2 completed.");
}


void init_tasks() {
    ESP_LOGI("TASK", "Initializing tasks...");

    // Initialize Task 1
    task_list[0].task_function = task1;
    memset(task_list[0].stack, 0xAA, sizeof(task_list[0].stack));  // Fill with 0xAA
    task_list[0].stack_pointer = &task_list[0].stack[STACK_SIZE - 1];
    ESP_LOGI("TASK", "Task 1 initialized at %p", task_list[0].stack_pointer);

    // Initialize Task 2
    task_list[1].task_function = task2;
    memset(task_list[1].stack, 0xAA, sizeof(task_list[1].stack));  // Fill with 0xAA
    task_list[1].stack_pointer = &task_list[1].stack[STACK_SIZE - 1];
    ESP_LOGI("TASK", "Task 2 initialized at %p", task_list[1].stack_pointer);
}


