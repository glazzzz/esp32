#include "esp_log.h"
#include "driver/ledc.h"

#define SERVO_GPIO      CONFIG_SERVO_GPIO

#define minValue 900  //  duty value for 0
#define maxValue  3800 // duty value for 180

static char *TAG = "servo";

const int bitSize =15;
int delta = maxValue - minValue;;
int time_period = 20000; // micro
int duty;

void configureServo(){
    duty = minValue ;
	ESP_LOGI(TAG, ">> task_servo1");
	ledc_timer_config_t timer_conf;
	timer_conf.bit_num    = LEDC_TIMER_15_BIT;
	timer_conf.freq_hz    = 50;
	timer_conf.speed_mode = LEDC_HIGH_SPEED_MODE;
	timer_conf.timer_num  = LEDC_TIMER_0;
	ledc_timer_config(&timer_conf);

	ledc_channel_config_t ledc_conf;
	ledc_conf.channel    = LEDC_CHANNEL_0;
	ledc_conf.duty       = duty;
	ledc_conf.gpio_num   = SERVO_GPIO;
	ledc_conf.intr_type  = LEDC_INTR_DISABLE;
	ledc_conf.speed_mode = LEDC_HIGH_SPEED_MODE;
	ledc_conf.timer_sel  = LEDC_TIMER_0;
	ledc_channel_config(&ledc_conf);
}

void setAngle(int target_angle){
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, duty+ (delta*(target_angle/180.0)) );
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
}
