# Tuya IoTOS Embeded Demo WiFi & BLE ts02n key drive

[English](./README.md) | [中文](./README_zh.md)

## Introduction 


This Demo is based on Tuya Smart Cloud Platform, Tuya Smart APP, IoTOS Embeded WiFi &Ble SDK, using Tuya WiFi/WiFi+BLE series modules and  TS02N touch chip quickly implements a touch key driver  , this demo provides the interface, the user can set the key input pin and key triggering function, and finally use the key registration function to register;When the button is pressed, the button prompt light will light up, and when the button is released, the prompt light will turn off, and the button callback function will be triggered to update the pressed button information to the mobile APP. 
## Quick start

### Compile and burn-in
+ Download [Tuya IoTOS Embeded WiFi & BLE sdk](https://github.com/tuya/tuya-iotos-embeded-sdk-wifi-ble-bk7231n) 

+ Download the demo to the apps directory of the SDK directory 

  ```bash
  $ cd apps
  $ git clone https://registry.code.tuya-inc.top/hardware_developer/tuya-iotos-embeded-demo-wifi-ble-ts02n-key-drive.git
  ```

+ Execute the following command in the SDK root directory to start compiling.

  ```bash
  sh build_app.sh apps/bk7231n_ts02n_key_demo bk7231n_ts02n_key_demo 1.0.0
  ```

+ Firmware burn-in license information please refer to: [Wi-Fi + BLE series module burn-in license](https://developer.tuya.com/cn/docs/iot/device-development/burn-and-authorization/burn-and-authorize-wifi-ble-modules/burn-and-authorize-wb-series-modules?id=Ka78f4pttsytd) 



### File description

```
├── src	
|    ├── app_driver
|    |    └── tuya_ts02n_key.c            //Key drive
|    |    └── tuya_gpio_control.c            //Key indicator light configuration
|    ├── tuya_device.c             //application layer entry file
|    └── tuya_app_ts02n_key.c           //primary application layer
|
├── include				//header directory
|    ├── app_driver_h
|    |    └── tuya_ts02n_key.h        
|    |    └── tuya_gpio_control.h            
|    ├── tuya_device.h
|    └── tuya_app_ts02n_key.h
|
└── output              //compile the product
```

<br>

### Application entry
Entry file: tuya_device.c

Important functions: device_init()

+ Call tuya_iot_wf_soc_dev_init_param() interface to initialize the SDK, configure the operating mode, the mating mode, and register various callback functions and store the firmware key and PID.
+ Calling the tuya_iot_reg_get_wf_nw_stat_cb() interface to register the device network status callback functions.
+ Call the application layer initialization function app_ts02n_key_init().

<br>

### dp point related

+ Send down dp point data stream: dev_obj_dp_cb() -> deal_dp_proc()
+ Report dp point interface: dev_report_dp_json_async()

| function name | OPERATE_RET dev_report_dp_json_async(IN CONST CHAR_T *dev_id,IN CONST TY_OBJ_DP_S *dp_data,IN CONST UINT_T cnt)|
| ---|--|
| devid | device id (if it is a gateway, MCU, SOC class device then devid = NULL; if it is a sub-device, then devid = sub-device_id)|
| dp_data | dp structure array name|
| cnt | number of elements of the dp structure array|
| return | OPRT_OK: Success Other: Failure |

### I/O List

|TS02N||
| --- | --- |
|key1_pin|PA8|
|key2_pin|PA7|
|led1_pin|PA24|
|led2_pin|PA26|



<br>



## Related Documents

Tuya Demo Center: https://developer.tuya.com/demo


<br>


## Technical Support

You can get support for Tuya by using the following methods:

- Developer Center: [https://developer.tuya.com](https://developer.tuya.com) 
- Help Center: [https://support.tuya.com/help](https://support.tuya.com/help) 
- Technical Support Work Order Center: [https://service.console.tuya.com](https://service.console.tuya.com/)


<br>


