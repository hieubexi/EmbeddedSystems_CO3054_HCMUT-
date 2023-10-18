/*
* creator/date: HieuHuuNguyen_2013149/Oct.11.2023
* course name/ID: Embedded systems/CO3054
*/ 

#include <stdio.h>
// RTOS services
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "FreeRTOSConfig.h"
// IDLE services
#include "esp_freertos_hooks.h"
// GPIO services
#include "driver/gpio.h"
#include "rom/gpio.h"
#include "esp_system.h"
#include "esp_log.h"
// configuration
#include "sdkconfig.h"

#define BUTTON GPIO_NUM_18
#define LED GPIO_NUM_17

const int student_id = 2013149;
static uint8_t  button_active_state = 0 ;
volatile uint32_t ulIdleCycleCount = 0UL ;


void set_up_gpio(){
    printf("Setting ...\n") ;
    gpio_pad_select_gpio(BUTTON);
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);

    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_level(LED, 0);
    printf("Done setting\n"); 
}
void vApplicationIdleHook (void){
    ulIdleCycleCount++;
}
void system_is_singing(void* pvParameter) {
    while(1){
        printf("I just wanna be part of your symphony\n");
        // Delay about 2 seconds
        // vTaskDelay(2000/ portTICK_PERIOD_MS);    
    }
    vTaskDelete(NULL);
}
void is_singing(void* pvParameter) {
    while(1){
        printf("I just wanna \n");
        // Delay about 2 seconds
        // vTaskDelay(2000/ portTICK_PERIOD_MS);    
    }
    vTaskDelete(NULL);
}
// musician play music all the time
void musician_is_playing(void* pvParameter){
    while (1)
    {
        printf("musician is playing %ld note\n", ulIdleCycleCount);
        // vTaskDelay(490/ portTICK_PERIOD_MS);
        // printf("musician is playing note\n");
    }
    vTaskDelete(NULL);
}
// Event task (high priority)
void someone_come_system(void* pvParameters){
    while (1)
    {
        if (gpio_get_level(BUTTON) == button_active_state){
            printf("Stop singing, turn on the led, please\n");
            gpio_set_level(LED, 1);
        }
        vTaskDelay(100/ portTICK_PERIOD_MS);
        gpio_set_level(LED, 0);
    }
    vTaskDelete(NULL);    
}


void app_main(void)
{
    printf("Lab 3: Prioritized scheduling with time slicing\n");
    set_up_gpio();
    
    xTaskCreatePinnedToCore(system_is_singing, "system_is_singing", 1024, NULL, 0, NULL, 0);
    xTaskCreatePinnedToCore(musician_is_playing, "musician_is_playing", 1024, NULL, 0, NULL, 0);
    xTaskCreatePinnedToCore(someone_come_system, "someone_come_system", 1024, NULL, 2, NULL, 0);
}
    