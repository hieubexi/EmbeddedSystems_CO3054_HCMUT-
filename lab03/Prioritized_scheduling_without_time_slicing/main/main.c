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

#define BUTTON GPIO_NUM_18
#define LED GPIO_NUM_17
#define LED_STATUS GPIO_NUM_2

// const int studentID = 2013149 ;
// this variable below is used to count the number of times that task1 ran
// const int student_id = 2013149;
static uint8_t  button_active_state = 0 ;
volatile uint32_t ulIdleCycleCount = 0UL ;
volatile uint32_t NumJackYelling = 0UL ;
volatile uint32_t numBTSsang = 0UL ;
volatile uint32_t numGDsang = 0UL ;

int64_t begin_system = 0UL;

char GDmsg[] = "* Ayo, what up VietNam, guess who is back!";

void set_up_gpio(){
    printf("********************************\n");
    printf("* Setting...\n") ;
    gpio_pad_select_gpio(BUTTON);
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);

    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_level(LED, 0);
    begin_system = esp_timer_get_time();
    printf("* Done setting\n"); 
    printf("********************************\n");
}

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
    int64_t GD_start = esp_timer_get_time();
    int lenMsg = strlen(GDmsg);
    printf("********************************\n");
    printf("* GD sing at  %lld ms\n", GD_start/1000);
    while (true){
        for (int i = 0; i < lenMsg; i++)
        {
            printf("%c", GDmsg[i]);
            // makeSystemBusy(50); 
            vTaskDelay(50 / portTICK_PERIOD_MS);
        }
        printf("\n") ;
        taskYIELD();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// This is higher priority task
void Jack_is_coming(void* pvParameter){
    int64_t Jack_start = esp_timer_get_time();
    printf("********************************\n");
    printf("* Jack come at  %lld ms\n", Jack_start/1000);
    printf("* Jack come and broke the show. his voice be like : \"$\" \n");
    while (true) {   
        makeSystemBusy(50); 
        printf("$");
        taskYIELD();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
void app_main(void) {
    set_up_gpio();
    xTaskCreatePinnedToCore(GD_is_singing,"Task1",5120, NULL, 1,NULL,0); //
    xTaskCreatePinnedToCore(Jack_is_coming,"Task3",5120, NULL, 10,NULL,0); //
}
