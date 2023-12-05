/*
* creator/date: Group-05/Oct.11.2023
* course name/ID: Embedded_Systems/CO3054
*/
// RTOS services
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// to have a time slicing you eed to configure some variables
// configUSE_PREEMPTION    ->  1
// configUSE_TIME_SLICING  -> 1
#include "FreeRTOSConfig.h"

#include "esp_timer.h"
// IDLE services
#include "esp_freertos_hooks.h"
// GPIO services
#include "driver/gpio.h"
#include "rom/gpio.h"
#include "esp_system.h"
#include "esp_log.h"
#include <stdio.h>
#include <string.h>
// configuration
#include "sdkconfig.h"
// #undef configUSE_TIME_SLICING
// #define configUSE_TIME_SLICING                       0




volatile uint32_t ulIdleCycleCount = 0UL ;

int64_t begin_system = 0UL;

char GDmsg[] = "* Ayo, what up VietNam, guess who is back!";
char BPmsg[] = "* BackPink in your area!";

void makeSystemBusy(int time  ){
    int64_t lStart = esp_timer_get_time();
    int64_t lEnd = lStart + time * 1000;
    while (esp_timer_get_time() < lEnd) {
        ; // do not thing in here
    }
}

void vApplicationIdleHook (void) {
    ulIdleCycleCount++;
}

void GD_is_singing(void* pvParameter){
    int lenMsg = strlen(GDmsg);
    printf("********************************\n");
    printf("* At %ld ms, GD sing \n",pdTICKS_TO_MS(xTaskGetTickCount()));
    while (true){
        for (int i = 0; i < lenMsg; i++)
        {
            printf("%c", GDmsg[i]);
            makeSystemBusy(50); 
            // vTaskDelay(50 / portTICK_PERIOD_MS);
        }
        printf("\n") ;
        taskYIELD();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void BP_is_singing(void* pvParameter){
    int lenMsg = strlen(BPmsg);
    printf("********************************\n");
    printf("* At %ld ms, BackPink sing \n", pdTICKS_TO_MS(xTaskGetTickCount()));
    while (true){
        for (int i = 0; i < lenMsg; i++)
        {
            printf("%c", BPmsg[i]);
            makeSystemBusy(50); 
        }
        printf("\n") ;
        taskYIELD();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
// This is higher priority task
void Jack_is_coming(void* pvParameter){
    printf("********************************\n");
    printf("* At %ld ms, Jack come\n", pdTICKS_TO_MS(xTaskGetTickCount()));
    printf("* At %ld ms, Jack come and broke the show. his voice be like : \"$\" \n", pdTICKS_TO_MS(xTaskGetTickCount()));
    while (true) {   
        makeSystemBusy(50); 
        printf("$");
        taskYIELD();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
void app_main(void) {
    xTaskCreatePinnedToCore(GD_is_singing,"Task1",5120, NULL, 1,NULL,0); 
    xTaskCreatePinnedToCore(BP_is_singing,"Task2",5120, NULL, 2,NULL,0); 
    xTaskCreatePinnedToCore(Jack_is_coming,"Task3",5120, NULL, 3,NULL,0); 
}
