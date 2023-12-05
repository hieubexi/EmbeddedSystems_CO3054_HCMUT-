/*
* creator/date: Group-05/Dec.04.2023
* course name/ID: Embedded systems/CO3054
*/

#include <stdio.h>
// RTOS services
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "freeRTOS/timers.h"
#include "esp_log.h"
// configuration
#include "sdkconfig.h"

#define TAG "System"
// Id for each timer
#define ahihi_ID 1
#define ihaha_ID 2
// Maximum couter of each timer
#define MAX_COUNT_AHIHI 10
#define MAX_COUNT_IHAHA 5
// define timer
TimerHandle_t xTimer_ahihi;
TimerHandle_t xTimer_ihaha;
TimerHandle_t xOneShot;
// Counter for task
static uint32_t ulCounter_0 = 0;
static uint32_t ulCounter_1 = 0;

void ATimerCallback(TimerHandle_t xTimer);
// define one shot call back function
// void oneShotTimer(TimerHandle_t xTimer);
void app_main(void)
{
  xTimer_ahihi = xTimerCreate("vTimer_0", pdMS_TO_TICKS(2000), pdTRUE, (void *)ahihi_ID, ATimerCallback);
  xTimer_ihaha = xTimerCreate("vTimer_1", pdMS_TO_TICKS(3000), pdTRUE, (void *)ihaha_ID, ATimerCallback);
  // xOneShot = xTimerCreate("oneShot", pdMS_TO_TICKS(9000), pdFALSE, (void *)15, oneShotTimer);
  // Check if timer is available 
  if (xTimerStart(xTimer_ahihi, 0) != pdPASS || 
      xTimerStart(xTimer_ihaha, 0) != pdPASS 
  // || xTimerStart(xOneShot, 0) != pdPASS
  )
  {
    ESP_LOGI(TAG, "At %ld, timer start failed", pdTICKS_TO_MS(xTaskGetTickCount()));
  }
}

// Call back function
void ATimerCallback(TimerHandle_t xTimer)
{
  uint32_t taskID = (uint32_t)pvTimerGetTimerID(xTimer);

  if (taskID == ahihi_ID)
  {
    ulCounter_0 += 1;
    printf("At %ld ms, count \"ahihi\" %ld times\n", pdTICKS_TO_MS(xTaskGetTickCount()), ulCounter_0);
    if (ulCounter_0 >= MAX_COUNT_AHIHI)
    {
      ESP_LOGI(TAG,"At %ld ms, STOP count \"ahihi\"", pdTICKS_TO_MS(xTaskGetTickCount()));
      xTimerStop(xTimer, 0);
    }
  }
  else if (taskID == ihaha_ID)
  {
    ulCounter_1 += 1;
    printf("At %ld ms, count \"ihaha\" %ld times\n", pdTICKS_TO_MS(xTaskGetTickCount()), ulCounter_1);
    if (ulCounter_1 >= MAX_COUNT_IHAHA)
    {
      ESP_LOGI(TAG,"At %ld ms, STOP count \"ihaha\"", pdTICKS_TO_MS(xTaskGetTickCount()));
      xTimerStop(xTimer, 0);
    }
  }
}
// test one shot timer
// void oneShotTimer(TimerHandle_t xTimer){
//   ESP_LOGI(TAG,"At %ld ms, ONE SHOT timer \"bum bum bum chiu\"", pdTICKS_TO_MS(xTaskGetTickCount()));
// }