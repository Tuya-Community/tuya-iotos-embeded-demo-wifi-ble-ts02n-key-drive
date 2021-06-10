/*
 * @Author: xjw
 * @email: fudi.xu@tuya.com
 * @LastEditors: xjw
 * @file name: app_ts02n_key.c
 * @Description: Main application files
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-5-29 15:22:03
 * @LastEditTime: 2021-05-29 17:35:04
 */
/* Includes ------------------------------------------------------------------*/
#include "tuya_iot_wifi_api.h"
#include "tuya_hal_thread.h"
#include "tuya_hal_system.h"
#include "uni_thread.h"
#include "tuya_gpio.h"
#include "uni_log.h"
/* Private includes ----------------------------------------------------------*/
#include "ts02n_key.h"
#include "app_ts02n_key.h"
#include "gpio_control.h"

/* Private function prototypes -----------------------------------------------*/
void key1_cb_fun();
void key2_cb_fun();
void key1_long_press_cb_fun();
void key2_long_press_cb_fun();
void key1_Low_level_cb_fun();
void key2_Low_level_cb_fun();
/* Private variables ---------------------------------------------------------*/
static enum key_status {
    no_key_press = 0,
    key1_normal_press,
    key2_normal_press,
    key1_long_press,
    key2_long_press
};
DP_VALUE_T key_value_s = {
    .dp_id = DP_KEY_VALUE,
    .value = no_key_press,
};
TS02N_KEY_DEF_S kettle_key_def_s = {
    .key_pin1 = TY_GPIOA_8,
    .key_pin2 = TY_GPIOA_7,
    .key1_cb = key1_cb_fun,
    .key2_cb = key2_cb_fun,
    .key1_long_press_cb = key1_long_press_cb_fun,
    .key2_long_press_cb = key2_long_press_cb_fun,
    .key1_Low_level_cb = key1_Low_level_cb_fun,
    .key2_Low_level_cb = key2_Low_level_cb_fun,
    .long_time_set = 5000,
    .scan_time = 100,
};
/* Private functions ---------------------------------------------------------*/
/**
 * @Function: app_ts02n_key_init
 * @Description: ts02n KEY INIT 
 * @Input: APP_MODE：Application mode
 * @Output: none
 * @Return: op_ret   execution result
 * @Others: 
 */
OPERATE_RET app_ts02n_key_init(IN APP_MODE mode)
{
    OPERATE_RET op_ret = OPRT_OK;

    if(APP_NORMAL == mode) {
        op_ret = ts02n_key_init(&kettle_key_def_s);
        if(op_ret != OPRT_OK) {
            PR_ERR("ts02n key init error");
        }
        led_gpio_init();
    }else {
        //not factory test mode
    }

    return op_ret;
}
/**
 * @Function: key1_cb_fun
 * @Description: The key1 button handle function
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void key1_cb_fun()
{   
    //Button press prompt
    led1_set(0);
    //Button press prompt
    key_value_s.value = key1_normal_press;
    app_report_all_dp_status();
    PR_DEBUG("key1 normal press");

}
/**
 * @Function: key2_cb_fun
 * @Description: The key2 button handle function
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void key2_cb_fun()
{
    //Button press prompt
    led2_set(0);
    //Button press prompt
    key_value_s.value = key2_normal_press;
    app_report_all_dp_status();
    PR_DEBUG("key1 normal press");



}
/**
 * @Function: key1_long_press_cb_fun
 * @Description: The key1 long press handle function
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void key1_long_press_cb_fun()
{

    led1_set(0);
    key_value_s.value = key1_long_press;
    app_report_all_dp_status();
    PR_DEBUG("key1 long press");

}
/**
 * @Function: key2_long_press_cb_fun
 * @Description: The key2 long press handle function
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void key2_long_press_cb_fun()
{

    led2_set(0);
    key_value_s.value = key2_long_press;
    app_report_all_dp_status();
    PR_DEBUG("key2 long press");

}
/**
 * @Function: key1_Low_level_cb_fun
 * @Description: key1 low level handle fuction
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void key1_Low_level_cb_fun()
{
    PR_DEBUG("key1 Low level");
    led1_set(1);
    
}
/**
 * @Function: key2_Low_level_cb_fun
 * @Description: key2 low level handle fuction
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
void key2_Low_level_cb_fun()
{
    led2_set(1);
    PR_DEBUG("key2 Low level");
}

/**
 * @Function: app_report_all_dp_status
 * @Description: app dp data report function
 * @Input: none 
 * @Output: none
 * @Return: none
 * @Others: 
 */
VOID app_report_all_dp_status(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    GW_WIFI_NW_STAT_E wifi_state = 0xFF;
    op_ret = get_wf_gw_nw_status(&wifi_state);
    if (OPRT_OK != op_ret) {
        PR_ERR("get wifi state err");
        return;
    }
    if (wifi_state <= STAT_AP_STA_DISC || wifi_state == STAT_STA_DISC) {
        return;
    }

    INT_T dp_cnt = 0;
    dp_cnt = 1;

    TY_OBJ_DP_S *dp_arr = (TY_OBJ_DP_S *)Malloc(dp_cnt*SIZEOF(TY_OBJ_DP_S));
    if(NULL == dp_arr) {
        PR_ERR("malloc failed");
        return;
    }

    memset(dp_arr, 0, dp_cnt*SIZEOF(TY_OBJ_DP_S));

    dp_arr[0].dpid = key_value_s.dp_id;
    dp_arr[0].type = PROP_ENUM;
    dp_arr[0].time_stamp = 0;
    dp_arr[0].value.dp_value = key_value_s.value;

    op_ret = dev_report_dp_json_async(NULL,dp_arr,dp_cnt);
    Free(dp_arr);
    if(OPRT_OK != op_ret) {
        PR_ERR("dev_report_dp_json_async relay_config data error,err_num",op_ret);
    }

    PR_DEBUG("dp_query report_all_dp_data");
    return;
}

/**
 * @Function: deal_dp_proc
 * @Description: dp data deal function
 * @Input: TY_OBJ_DP_S 
 * @Output: none
 * @Return: none
 * @Others: 
 */
VOID deal_dp_proc(IN CONST TY_OBJ_DP_S *root)
{
    UCHAR_T dpid;

    dpid = root->dpid;
    PR_DEBUG("dpid:%d",dpid);
    
    switch (dpid) {
    
    case 0:

        break;
    default:
        break;
    }

    app_report_all_dp_status();

    return;

}