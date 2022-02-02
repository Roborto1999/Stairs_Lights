/****************************** - Library Includes - *******************************/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "sdkconfig.h"
#include "esp_err.h"
#include "esp_system.h"
#include "esp_log.h"
#include "math.h"
/******************************** - User Includes - ********************************/
#include "led.h"
/*********************************** - Defines - ***********************************/
#define BLINK_GPIO_1 2
/************************************ - Enums - ************************************/
/********************************** - Typedefs - ***********************************/
/********************************* - Structures - **********************************/
/**************************** - Function Prototypes - ******************************/
static void blink_led_1();
static void blink_led_2();
static void configure_led();
static void setup_tasks();
/********************************* - Constants - ***********************************/
static const char *TAG = "example";
static const int rate_1 = 500;
/********************************* - Variables - ***********************************/
/***************************** - Public Functions - ********************************/
void app_main(void)
{

    /* Configure the peripheral according to the LED type */
    configure_led();
    setup_tasks();
}
/***************************** - Private Functions - *******************************/

static void blink_led_1(void *parameter)
{
    while (1)
    {
        /* Set the GPIO level according to the state (LOW or HIGH)*/
        gpio_set_level(BLINK_GPIO_1, 1);
        vTaskDelay(rate_1 / portTICK_PERIOD_MS);
        gpio_set_level(BLINK_GPIO_1, 0);
        vTaskDelay(rate_1 / portTICK_PERIOD_MS);
    }
}
static void blink_led_2(void *parameter)
{
    while (1)
    {
        led_fade_too_num(6000, 3000);

        vTaskDelay(4000 / portTICK_PERIOD_MS);

        led_fade_too_num(0, 3000);

        vTaskDelay(4000 / portTICK_PERIOD_MS);
    }
}

static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO_1);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO_1, GPIO_MODE_OUTPUT);
    led_setup();
}

static void setup_tasks(void)

{
    xTaskCreatePinnedToCore( // Use xTaskCreate() in vanilla FreeRTOS
        blink_led_1,         // Function to be called
        "Toggle 1",          // Name of task
        1024,                // Stack size (bytes in ESP32, words in FreeRTOS)
        NULL,                // Parameter to pass to function
        1,                   // Task priority (0 to configMAX_PRIORITIES - 1)
        NULL,                // Task handle
        0);                  // Run on one core for demo purposes (ESP32 only)

    // Task to run forever
    xTaskCreatePinnedToCore( // Use xTaskCreate() in vanilla FreeRTOS
        blink_led_2,         // Function to be called
        "Toggle 2",          // Name of task
        1024,                // Stack size (bytes in ESP32, words in FreeRTOS)
        NULL,                // Parameter to pass to function
        1,                   // Task priority (0 to configMAX_PRIORITIES - 1)
        NULL,                // Task handle
        1);                  // Run on one core for demo purposes (ESP32 only)
}