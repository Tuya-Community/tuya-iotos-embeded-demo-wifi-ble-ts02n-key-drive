# Tuya IoTOS Embedded Wi-Fi & Bluetooth LE Touch Sensor Driver

[English](./README.md) | [中文](./README_zh.md)

## Overview

In this demo, we will show you how to implement a TS02N-based touch sensor driver. Based on the [Tuya IoT Platform](https://iot.tuya.com/), we use Tuya's Wi-Fi and Bluetooth LE combo module, SDK, and the Tuya Smart app to connect the touch sensor to the cloud. The interfaces provided in this demo allow you to set the input pin and the trigger function. Then, register the function to implement your custom setting. The LED is on when the sensor is touched and is off when the sensor is released. The key callback can synchronize the touch key event to the mobile app.

## Get started

### Compile and flash

+ Download [Tuya IoTOS Embedded Wi-Fi & Bluetooth LE SDK](https://github.com/tuya/tuya-iotos-embeded-sdk-wifi-ble-bk7231n).

+ Clone this demo to the `app` folder in the downloaded SDK.

  ```bash
  $ cd apps
  $ git clone https://registry.code.tuya-inc.top/hardware_developer/tuya-iotos-embeded-demo-wifi-ble-ts02n-key-drive.git
  ```
+ Run the following command in the SDK root directory to start compiling.

  ```bash
  sh build_app.sh apps/bk7231n_ts02n_key_demo bk7231n_ts02n_key_demo 1.0.0
  ```

+ For more information about flashing and authorization, see [Flash Firmware to and Authorize WB Series Modules](https://developer.tuya.com/en/docs/iot/device-development/burn-and-authorization/burn-and-authorize-wifi-ble-modules/burn-and-authorize-wb-series-modules?id=Ka78f4pttsytd).



### File introduction

```
├── src	
|    ├── app_driver
|    |    └── tuya_ts02n_key.c            // Touch sensor driver
|    |    └── tuya_gpio_control.c            // LED configuration
|    ├── tuya_device.c             // Entry file of the application layer
|    └── tuya_app_ts02n_key.c            // Main application layer
|
├── include 			  // Header directory
|    ├── app_driver_h
|    |    └── tuya_ts02n_key.h            // Touch sensor driver
|    |    └── tuya_gpio_control.h            // LED configuration
|    ├── tuya_device.h
|    └── tuya_app_ts02n_key.h
|
└── output              // Production
```

### Entry to application

Entry file: `tuya_device.c`

Function: `device_init()`

+ Call `tuya_iot_wf_soc_dev_init_param()` for SDK initialization to configure working mode and pairing mode, register callbacks, and save the firmware key and PID.
+ Call `tuya_iot_reg_get_wf_nw_stat_cb()` to register callback of device network status.
+ Call the initialization function `app_ts02n_key_init()` in the application layer.


### Data point (DP)

+ Send DP data: `dev_obj_dp_cb() -> deal_dp_proc()`
+ Report DP data: `dev_report_dp_json_async()`

| Function name | OPERATE_RET dev_report_dp_json_async(IN CONST CHAR_T *dev_id,IN CONST TY_OBJ_DP_S *dp_data,IN CONST UINT_T cnt) |
|---|---|
| devid | For gateways and devices built with the MCU or SoC, the `devid` is NULL. For sub-devices, the `devid` is `sub-device_id`. |
| dp_data | The name of DP struct array |
| cnt | The number of elements in the DP struct array |
| Return | `OPRT_OK`: success. Other values: failure. |

### Pin configuration

| TS02N |   |
| --- | --- |
| key1_pin | PA8 |
| key2_pin | PA7 |
| led1_pin | PA24 |
| led2_pin | PA26 |

## Reference

[Tuya Project Hub](https://developer.tuya.com/demo)


## Technical support

You can get support from Tuya with the following methods:

+ [Service & Support](https://service.console.tuya.com)
+ [Tuya IoT Developer Platform](https://developer.tuya.com/en/)
+ [Help Center](https://support.tuya.com/en/help)

