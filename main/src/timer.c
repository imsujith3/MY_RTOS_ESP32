#include "driver/gptimer.h"
#include "esp_log.h"
#include "scheduler.h"
#include "esp_attr.h"  // Ensure IRAM_ATTR is defined

#define TIMER_INTERVAL_US 1000000  // 1 second

static const char *TAG = "GPTimer";
static gptimer_handle_t gptimer = NULL;

// 🔹 Declare the ISR function **before** init_timer()
bool IRAM_ATTR timer_isr_handler(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx);

void init_timer() {
    ESP_LOGI(TAG, "Initializing GPTimer...");

    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1000000
    };

    if (gptimer_new_timer(&timer_config, &gptimer) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create GPTimer!");
        return;
    }

    gptimer_alarm_config_t alarm_config = {
        .alarm_count = TIMER_INTERVAL_US,
        .reload_count = 0,
        .flags.auto_reload_on_alarm = true
    };

    if (gptimer_set_alarm_action(gptimer, &alarm_config) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set alarm action!");
        return;
    }

    gptimer_event_callbacks_t cbs = {
        .on_alarm = timer_isr_handler  // Use declared function
    };

    if (gptimer_register_event_callbacks(gptimer, &cbs, NULL) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to register GPTimer event callbacks!");
        return;
    }

    if (gptimer_enable(gptimer) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to enable GPTimer!");
        return;
    }

    if (gptimer_start(gptimer) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start GPTimer!");
        return;
    }

    ESP_LOGI(TAG, "GPTimer started with %d us interval", TIMER_INTERVAL_US);
}

// 🔹 Define the ISR function **after** init_timer()
bool IRAM_ATTR timer_isr_handler(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx) {
    //ESP_EARLY_LOGI(TAG, "Timer interrupt triggered!"); // Log from ISR
    task_switch();
    return true;
}
