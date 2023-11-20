/*
 * creator/date: HieuHuuNguyen_2013149/Nov.17.11
 * course name/ID: Embedded Systems/CO3054/
 */
#include <stdio.h>

// RTOS services
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// GPIO services
#include "esp_system.h"
#include "esp_log.h"
// configuration
#include "sdkconfig.h"

#include "queueConfig.h"

QueueHandle_t perform_set;

static uint16_t numAvalQueue;

static const char *TAG = "LAB4";
static char *god_lyrics[] = {
    "Once you play God, once you play God",
    "They're gonna crumble one by one",
    "Then we gon' ride right into the sun",
    "Like it's the day my kingdom come",
    "Baby, we're",
    "Go-Go-Go-Go-Go-Gods"};
int length_lyrics=sizeof(god_lyrics) / sizeof(god_lyrics[0]);
lyric_t create_lyric(uint32_t input_index, char *input_content)
{
    lyric_t *self = malloc(sizeof(lyric_t));
    self->index = input_index;
    self->content = input_content;
    return *self;
}
// Just print some information
void set_up()
{
    printf("********************************\n");
    printf("* Queue length: %d\n", __MAXLEN__);
    printf("* Max ID number: %d\n", __NOISE_VOLUME__);
    printf("********************************\n");
}

// this function send them to a queue
void send_lyric(QueueHandle_t queue, lyric_t self)
{
    if (self.index < 100)
    {
        ESP_LOGI(TAG, "[Send] at %ldms, Send item to queue, ID: %ld, Topic: \"%s\"", pdTICKS_TO_MS(xTaskGetTickCount()), self.index, self.content);
        // printf("* at %ldms, NewJeans want to sing the %ld sentence.\n* %s\n", pdTICKS_TO_MS(xTaskGetTickCount()), self.index, self.content);
    }
    else
    {
        ESP_LOGI(TAG, "[Send] at %ldms, [Noise item], ID: %ld, Topic: \"%s\"", pdTICKS_TO_MS(xTaskGetTickCount()), self.index, self.content);
        // printf("* at %ldms, Noise voice, the %ld sentence.\n* %s\n", pdTICKS_TO_MS(xTaskGetTickCount()), self.index, self.content);
    }
    if (xQueueSend(queue, (void *)&self, (TickType_t)0) != pdTRUE)
    {
        ESP_LOGI(TAG, "[Queue] Unsuccessful! No slot availiable in queue, queue is full");
        printf("* at %ldms, NewJeans do not want to sing anymore, they are \"OVERLOADED\"\n", pdTICKS_TO_MS(xTaskGetTickCount()));
    }
    else
    {
        numAvalQueue =  uxQueueSpacesAvailable(perform_set);
        ESP_LOGI(TAG, "[Queue] Successful! %d/%d slot left in queue", numAvalQueue, __MAXLEN__);
    }
    printf("\n");
}

// this function presents the reception task
// In this lab, this function is distributed lyrics to sing
void distribute_lyrics(void *pvParameter)
{
    // Create queue
    perform_set = xQueueCreate(__MAXLEN__, sizeof(lyric_t));

    // Create valid items
    lyric_t lyric[length_lyrics];
    for (uint32_t i = 0; i < length_lyrics; i++)
    {
        lyric[i] = create_lyric(i + 1, god_lyrics[i]);
    }
    // Create some noise items
    lyric_t noise_sentence1 = create_lyric(999, "!T@#1$&*.V,#$D/");
    lyric_t noise_sentence2 = create_lyric(766, "!H@#I$&E*.,U#$/");
    lyric_t noise_sentence3 = create_lyric(382, "g!@#g$&w*.,p#$/");

    int idx=0;
    for(;idx<length_lyrics/2;idx++){
        send_lyric(perform_set, lyric[idx]);
    }
    // send_lyric(perform_set, lyric[0]);
    // send_lyric(perform_set, lyric[1]);
    // send_lyric(perform_set, lyric[2]);
    // send noise
    send_lyric(perform_set, noise_sentence1);
    for(;idx<length_lyrics-length_lyrics/6;idx++){
        send_lyric(perform_set, lyric[idx]);
    }
    // send_lyric(perform_set, lyric[3]);
    // send_lyric(perform_set, lyric[4]);
     // send noise
    send_lyric(perform_set, noise_sentence2);
    for(;idx<length_lyrics;idx++){
        send_lyric(perform_set, lyric[idx]);
    }
    // send_lyric(perform_set, lyric[5]);
     // send noise
    send_lyric(perform_set, noise_sentence3);

    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// some functional methods

// found a noise item, handle it but not execute, also remove it from queue
// in this lab, NewJeans will not sing noise sentences
void removeNoise(void *pvParameter)
{
    while (1)
    {
        lyric_t self;
        if (xQueuePeek(perform_set, (void *)&self, (TickType_t)5) == pdTRUE)
        {
            if (self.index > __NOISE_VOLUME__)
            {
                ESP_LOGI(TAG, "[Noise] at %ld, Found a NOISE (ID > %d) ", pdTICKS_TO_MS(xTaskGetTickCount()), __NOISE_VOLUME__);
                ESP_LOGI(TAG, "[Noise] at %ld, Remove noise, ID: %ld, Topic: \"%s\"", pdTICKS_TO_MS(xTaskGetTickCount()), self.index, self.content);
                xQueueReceive(perform_set, (void *)&self, (TickType_t)5);
                printf("* NewJeans not sing this noise sentence: %s\n", self.content);
                printf("\n");
            }
            else
            {
                // printf("* This is not a noise\n");
            }
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// hadle and excuted the item in queue
// sing a song
void sing(void *pvParameter)
{
    while (1)
    {
        lyric_t self;
        if (xQueuePeek(perform_set, (void *)&self, (TickType_t)5) == pdTRUE)
        {
            if (self.index <= __NOISE_VOLUME__)
            {
                ESP_LOGI(TAG, "[Receiver] at %ldms, Handle valid item  ", pdTICKS_TO_MS(xTaskGetTickCount()));
                ESP_LOGI(TAG, "[Receiver] at %ldms, Excuted valid item, ID: %ld, Topic: \"%s\"", pdTICKS_TO_MS(xTaskGetTickCount()), self.index, self.content);
                xQueueReceive(perform_set, (void *)&self, (TickType_t)5);
                printf("* NewJeans sing the %ld lyric\n* %s\n", self.index, self.content);
                printf("\n");
            }
            else
            {
                // printf("* This is a noise\n");
            }
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    set_up();
    esp_log_level_set(TAG, ESP_LOG_INFO);
    xTaskCreatePinnedToCore(distribute_lyrics, "distribute_lyrics", 4096, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(removeNoise, "removeNoise", 4096, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(sing, "sing", 4096, NULL, 1, NULL, 0);
}