/*
 * @Author: xjw
 * @email: fudi.xu@tuya.com
 * @LastEditors: xjw
 * @file name: app_ts02n_key.h
 * @Description: 
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2021-05-29 16:50:03
 * @LastEditTime: 2021-05-29 16:50:14
 */

#ifndef __APP_TS02N_KEY_H__
#define __APP_TS02N_KEY_H__

#include "tuya_cloud_error_code.h"
#include "tuya_cloud_com_defs.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */
/* Exported constants --------------------------------------------------------*/              
/***********************************************************
*************************variable define********************
***********************************************************/
#define DP_KEY_VALUE 101

typedef enum{
    APP_NORMAL,       //normal mode
    APP_PRODTEST      //prodact test mode
}APP_MODE;


typedef struct {
    UINT8_T dp_id;
    
    int value;
}DP_VALUE_T;
/********************************************************************************
 * FUNCTION:       app_ts02n_key_init
 * DESCRIPTION:    application initialization
 * INPUT:          mode:application mode
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         none
 * HISTORY:        2021-04-29
 *******************************************************************************/
OPERATE_RET app_ts02n_key_init(IN APP_MODE mode);

/********************************************************************************
 * FUNCTION:       deal_dp_proc
 * DESCRIPTION:    deal the data sented by app
 * INPUT:          root:app issued data structure
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         none
 * HISTORY:        2021-04-29
 *******************************************************************************/
VOID deal_dp_proc(IN CONST TY_OBJ_DP_S *root);

/*********************************************************************************
 * FUNCTION:       app_report_all_dp_status
 * DESCRIPTION:    report all dp date
 * INPUT:          none
 * OUTPUT:         none
 * RETURN:         none
 * OTHERS:         dp_cnt needs to be modified when adding or deleting the dp function
 * HISTORY:        2021-04-29
 *******************************************************************************/
VOID app_report_all_dp_status(VOID);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* __LIHGT_INIT_H__ */