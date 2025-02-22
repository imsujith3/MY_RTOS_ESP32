#include "task.h"
#include "scheduler.h"
#include "timer.h"
#include "esp_task_wdt.h"
#include "esp_log.h"
#include "inttypes.h"

void app_main() {
    esp_task_wdt_deinit();  // Disable watchdog timer
    ESP_LOGI("RTOS", "Starting custom RTOS...");

    init_tasks();  // Initialize tasks
    init_timer();  // Start the timer for task switching

    while (1) {
        ESP_LOGI("Memory", "Free Heap: %lu bytes", esp_get_free_heap_size());
        vTaskDelay(pdMS_TO_TICKS(1000));  
    }
}
