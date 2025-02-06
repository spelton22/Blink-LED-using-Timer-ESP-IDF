#include <esp_timer.h>
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define TIMER2_INTERVAL 1000000
#define TIMER1_INTERVAL 500000

#define LED_PIN 35 //TO_BE_FILLED_IN
#define EX_LED_PIN 1

static void timer1_callback(void * arg){
  if(gpio_get_level(LED_PIN) == 0){
    gpio_set_level(LED_PIN, 1 );
  }else if(gpio_get_level(LED_PIN) == 1){
    gpio_set_level(LED_PIN, 0 );
  }
}

static void timer2_callback(void * arg){
  if(gpio_get_level(EX_LED_PIN) == 0){
    gpio_set_level(EX_LED_PIN, 1 );
  }else if(gpio_get_level(EX_LED_PIN) == 1){
    gpio_set_level(EX_LED_PIN, 0 );
  }
}



void app_main() {
  // Configure the LED pin
  gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << LED_PIN),
    .mode = GPIO_MODE_INPUT_OUTPUT , 
  };
  gpio_config(&io_conf);

  gpio_config_t io_conf2 = {
    .pin_bit_mask = (1ULL << EX_LED_PIN),
    .mode = GPIO_MODE_INPUT_OUTPUT , 
  };
  gpio_config(&io_conf2);

  esp_timer_create_args_t timer1_args = {
    .callback = &timer1_callback,
    .name = "timer1",
  };

  esp_timer_create_args_t timer2_args = {
    .callback = &timer2_callback,
    .name = "timer2",
  };

  esp_timer_handle_t timer1;
  esp_timer_create(&timer1_args, &timer1);
  esp_timer_start_periodic(timer1, TIMER1_INTERVAL);

  esp_timer_handle_t timer2;
  esp_timer_create(&timer2_args, &timer2);
  esp_timer_start_periodic(timer2, TIMER2_INTERVAL);

 
  // gpio_set_level(LED_PIN, 1 /*TO_BE_FILLED_IN*/);
  // vTaskDelay(50 /*TO_BE_FILLED_IN*/);
  // gpio_set_level(LED_PIN, 0 /*TO_BE_FILLED_IN*/);
  // vTaskDelay(50 /*TO_BE_FILLED_IN*/);
  
  // gpio_set_level(EX_LED_PIN, 1);
  // vTaskDelay(100 /*TO_BE_FILLED_IN*/);
  // gpio_set_level(EX_LED_PIN, 0);
  // vTaskDelay(100 /*TO_BE_FILLED_IN*/);

}