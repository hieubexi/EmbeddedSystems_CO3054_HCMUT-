#ifndef QUEUE_CONFIG_H
#define QUEUE_CONFIG_H
#include <string.h>
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
// [Config available] Maximum length of queue
#define __MAXLEN__ 10
//[Config available]  If some item has id larger than __NOISE_VOLUME__, it will be labeled as noise
#define __NOISE_VOLUME__ 100
typedef struct
{
    uint32_t index;
    char *content;
} lyric_t;
// this function is create a object
// In this lab "object" is a lyric
lyric_t create_lyric(uint32_t input_index, char *input_content);
#endif 