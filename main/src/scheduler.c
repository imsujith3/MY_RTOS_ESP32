#include "scheduler.h"
#include "task.h"
#include "esp_log.h"
#include "stddef.h"

extern tcb_t task_list[];
extern int current_task;

// Disable and enable interrupts manually
static inline void disable_interrupts() { __asm__ volatile("rsil a2, 3"); }
static inline void enable_interrupts() { __asm__ volatile("rsil a2, 0"); }

void print_memory_dump(void *addr, int size) {
    uint8_t *ptr = (uint8_t *)addr;
    for (int i = 0; i < size; i++) {
        if (i % 16 == 0) ESP_EARLY_LOGI("MEMDUMP", "\n");
        ESP_EARLY_LOGI("MEMDUMP", "%02X ", ptr[i]);
    }
}

void task_switch() {
    disable_interrupts();
    current_task = (current_task + 1) % MAX_TASKS;
    enable_interrupts();

   if(current_task == 0) {
        task_list[0].task_function();
    } else {
        task_list[1].task_function();
    }
}




