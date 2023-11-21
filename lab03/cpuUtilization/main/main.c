/*
* creator/date: Group-06/Nov.16.2023
* course name/ID: Embedded Systems/CO3054
*/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "sdkconfig.h"
#include "esp_err.h"
#include "esp_log.h"

static const char *TAG0 = "CPU0";
static const char *TAG1 = "CPU1";
static uint64_t idle0Calls = 0;
static uint64_t idle1Calls = 0;
// MaxIdleCalls represents the maximum number of idle calls (total time)
#if defined(CONFIG_ESP32_DEFAULT_CPU_FREQ_240)
static const uint64_t MaxIdleCalls = 1855000;
#elif defined(CONFIG_ESP32_DEFAULT_CPU_FREQ_160)
static const uint64_t MaxIdleCalls = 1233100;
#else
#error "Unsupported CPU frequency" 
#endif

static bool idle_task_0()
{
	idle0Calls += 1;
	return false;
}

static bool idle_task_1()
{
	idle1Calls += 1;
	return false;
}

static void perform_task(void *args)
{
	while (1)
	{
		float idle0 = idle0Calls;
		float idle1 = idle1Calls;
		// calculate cpu utilization
		int utilize_cpu0 = 100.f -  idle0 / MaxIdleCalls * 100.f;
		int utilize_cpu1 = 100.f - idle1 / MaxIdleCalls * 100.f;

		printf("[CPU0] At %ld ms, core utilization %d%%\n", pdTICKS_TO_MS(xTaskGetTickCount()),  utilize_cpu0);
		printf("[CPU1] At %ld ms, core utilization %d%%\n", pdTICKS_TO_MS(xTaskGetTickCount()), utilize_cpu1);
		// Config delay
		vTaskDelay(1000/ portTICK_PERIOD_MS);
		// Reset idle counter
		if(idle0Calls >= MaxIdleCalls || idle1Calls >= MaxIdleCalls){
			idle0Calls = 0;
			idle1Calls = 0;
			ESP_LOGI(TAG0, "At %ld ms, Reset idle counter", pdTICKS_TO_MS(xTaskGetTickCount()));
			ESP_LOGI(TAG1, "At %ld ms, Reset idle counter", pdTICKS_TO_MS(xTaskGetTickCount()));
		}
	}
	vTaskDelete(NULL);
}


void app_main(void) {
	printf("********************************\n");
   	ESP_ERROR_CHECK(esp_register_freertos_idle_hook_for_cpu(idle_task_0, 0));
	ESP_ERROR_CHECK(esp_register_freertos_idle_hook_for_cpu(idle_task_1, 1));
	xTaskCreate(perform_task, "perform", 2048, NULL, 1, NULL);
}