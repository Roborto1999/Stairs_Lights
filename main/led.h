#ifndef STAIR_LIGHTS_PROJECT_LED_HEADER
#define STAIR_LIGHTS_PROJECT_LED_HEADER
/******************************** - User Includes - ********************************/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "led.h"
/*********************************** - Defines - ***********************************/
/************************************ - Enums - ************************************/
/********************************** - Typedefs - ***********************************/
/********************************* - Structures - **********************************/
/**************************** - Function Prototypes - ******************************/
//static bool cb_ledc_fade_end_event(const ledc_cb_param_t *param, void *user_arg);
void led_fade_too_num(uint32_t targetDuty, int time);//, SemaphoreHandle_t counting_sem);
void led_setup();//SemaphoreHandle_t counting_sem);
/****************************** - Global Variables - *******************************/

#endif //STAIR_LIGHTS_PROJECT_LED_HEADER