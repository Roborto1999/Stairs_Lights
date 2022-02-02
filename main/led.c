/****************************** - Library Includes - *******************************/
/******************************** - User Includes - ********************************/
#include "led.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "led.h"
/*********************************** - Defines - ***********************************/
#define LEDC_HS_TIMER LEDC_TIMER_0
#define LEDC_HS_MODE LEDC_HIGH_SPEED_MODE
#define LEDC_HS_CH0_GPIO (18)
#define LEDC_HS_CH0_CHANNEL LEDC_CHANNEL_0

#define LEDC_TEST_CH_NUM (1)
#define LEDC_TEST_DUTY (8000)
#define LEDC_TEST_FADE_TIME (3000)
/************************************ - Enums - ************************************/
/********************************** - Typedefs - ***********************************/
/********************************* - Structures - **********************************/
/**************************** - Function Prototypes - ******************************/
//static bool cb_ledc_fade_end_event(const ledc_cb_param_t *param, void *user_arg);
void led_fade_too_num(uint32_t targetDuty, int time);//, SemaphoreHandle_t counting_sem);
void led_setup();//SemaphoreHandle_t counting_sem);
/********************************* - Constants - ***********************************/
/********************************* - Variables - ***********************************/


ledc_timer_config_t ledc_timer = {
    .duty_resolution = LEDC_TIMER_13_BIT, // resolution of PWM duty
    .freq_hz = 5000,                      // frequency of PWM signal
    .speed_mode = LEDC_HS_MODE,           // timer mode
    .timer_num = LEDC_HS_TIMER,           // timer index
    .clk_cfg = LEDC_AUTO_CLK,             // Auto select the source clock
};

ledc_channel_config_t ledc_channel =
    {
        .channel = LEDC_HS_CH0_CHANNEL,
        .duty = 0,
        .gpio_num = LEDC_HS_CH0_GPIO,
        .speed_mode = LEDC_HS_MODE,
        .hpoint = 0,
        .timer_sel = LEDC_HS_TIMER,
        .flags.output_invert = 0};
/***************************** - Public Functions - ********************************/
// static bool cb_ledc_fade_end_event(const ledc_cb_param_t *param, void *user_arg)
// {
//     portBASE_TYPE taskAwoken = pdFALSE;

//     if (param->event == LEDC_FADE_END_EVT)
//     {
//         SemaphoreHandle_t counting_sem_2 = (SemaphoreHandle_t)user_arg;
//         xSemaphoreGiveFromISR(counting_sem_2, &taskAwoken);
//     }

//     return (taskAwoken == pdTRUE);
// }
void led_fade_too_num(uint32_t targetDuty, int time)//, SemaphoreHandle_t counting_sem)
{
    ledc_set_fade_with_time(ledc_channel.speed_mode,
                            ledc_channel.channel, targetDuty, time);
    ledc_fade_start(ledc_channel.speed_mode,
                    ledc_channel.channel, LEDC_FADE_NO_WAIT);

    //xSemaphoreTake(counting_sem, portMAX_DELAY);
}
void led_setup()//SemaphoreHandle_t counting_sem)
{
    ledc_timer_config(&ledc_timer);
    ledc_channel_config(&ledc_channel);
    ledc_fade_func_install(0);
    //ledc_cbs_t callbacks = {
       // .fade_cb = cb_ledc_fade_end_event};
    //ledc_cb_register(ledc_channel.speed_mode, ledc_channel.channel, &callbacks, (void *)counting_sem);
}
/***************************** - Private Functions - *******************************/