/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 * creator/date: HieuHuuNguyen_2013149/Sep.28.2023
 * 
 */

#include "driver/gpio.h"
#include "rom/gpio.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <stdio.h>


#define BUTTON GPIO_NUM_18
#define LED GPIO_NUM_17

const int studentID = 2013149 ;
int count_run_task_1 = 0;
static uint8_t button_default_state = 0;
// Features functions

// set up phase 
void setup(){
    printf("Setup gpio\n");
    // Set up for BUTTON
    gpio_pad_select_gpio(BUTTON);  
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);

    // set up for LED
    gpio_set_direction(LED,GPIO_MODE_OUTPUT);
    gpio_set_level(LED,0);

}
// Print student every second
void printStudentID(void *pvParameter){
    while(1){
        printf("%d times execution task 1 | Student's ID: %d\n",count_run_task_1,studentID);
        count_run_task_1++;
        // Delay about 1 second
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
// print  ESP32 when button is pressed
void eventPrintESP32(void *pvParameter){
    while (1)
    {   
        if(gpio_get_level(BUTTON) == button_default_state) {
                printf("Task 2: ESP32\n");
                gpio_set_level(LED,1);   
        }
        // Debounce for button press
        vTaskDelay(200 / portTICK_PERIOD_MS);
        gpio_set_level(LED,0);

    }
    // Delete the task. This will never be reached.
    vTaskDelete(NULL);
}
void holding_time(){
    while (1)
    {
        
    }
    
}
// main function
void app_main(void)
{
    // esp_rom_gpio_pad_select_gpio(BUTTON);    

    // gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);
    // gpio_pad_select_gpio(BUTTON);
    // gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
    // gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);
    printf("Hello world!\n");
    setup();
    xTaskCreate(printStudentID, "printStudentID", 2048, NULL, 1, NULL);
    xTaskCreate(eventPrintESP32, "eventPrintESP32", 2048, NULL, 2, NULL);

}
