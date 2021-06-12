/*
 * @file name: gpio_control.c
 * @Descripttion: gpio control file
 * @Author: xjw
 * @email: fudi.xu@tuya.com
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-05-29 16:45:15
 * @LastEditors: xjw
 * @LastEditTime: 2021-05-29 17:05:48
 */
#include "tuya_gpio_control.h"

#define led1_pin 24
#define led2_pin 26
/**
 * @Function: led_gpio_init
 * @Description: gpio init
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void led_gpio_init()
{
    //led pin init
    tuya_pin_init(led1_pin, TUYA_PIN_MODE_OUT_PP_HIGH);
    tuya_pin_init(led2_pin, TUYA_PIN_MODE_OUT_PP_HIGH);
}

/**
 * @Function: led1_set
 * @Description: led1
 * @Input: BOOL_T bONOFF
 * @Output: none
 * @Return: none
 * @Others: 
 */
void led1_set(IN     BOOL_T bONOFF)
{
    static bool last_status = 0;
    if(last_status != bONOFF) {
        if(bONOFF == TRUE) {
        tuya_pin_write(led1_pin, TUYA_PIN_LOW);
        }else {
        tuya_pin_write(led1_pin, TUYA_PIN_HIGH);
        }
        last_status = bONOFF;
    }

}
/**
 * @Function: led2_set
 * @Description: led2
 * @Input: BOOL_T bONOFF
 * @Output: none
 * @Return: none
 * @Others: 
 */
void led2_set(IN     BOOL_T bONOFF)
{
    static bool last_status = 0;
    if(last_status != bONOFF) {
        if(bONOFF == TRUE) {
        tuya_pin_write(led2_pin, TUYA_PIN_LOW);
        }else {
        tuya_pin_write(led2_pin, TUYA_PIN_HIGH);
        }
        last_status = bONOFF;
    }
}