#ifndef UTILS_H
#define UTILS_H

#include <ESP8266WiFi.h>
//#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <EEPROM.h>

#define DEBUG

#define PRINT_PORT              Serial
#define PRINT_LOG(msg)          {PRINT_PORT.print(millis()), PRINT_PORT.print(" "), PRINT_PORT.println(msg);}
#define PRINTF_LOG(msg, ...)    {PRINT_PORT.print(millis()), PRINT_PORT.print(" "), PRINT_PORT.printf(msg, ##__VA_ARGS__);}

#if defined(DEBUG)
    #define DEBUG_PRINT(msg)  PRINT_LOG(msg)
    #define DEBUG_PRINTF(msg, ...)  PRINTF_LOG(msg, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(...)
    #define DEBUG_PRINTF(...)
#endif

// 指示灯引脚定义
#define LED_PIN            2    //BUILTIN_LED
#define BOARD_PWM_MAX      1024

#define fw_VERSION         (const char *)"0.0.1"
#define fwHost             "192.168.1.108" //"angus.fun" 
#define fwHostPort          6051    //5000
#define fwHostUrl           "/firmware/esp8266"
#define fwHostHasNewUrl     "/hasNewfirmware/"

#define EEPROM_CONFIG_START 0

struct ConfigStore {
    uint32_t  magic;
    char      version[9];
    uint8_t   flagConfig:1;  // 进入配置模式
    uint8_t   flagApFail:1;  // AP故障
    uint8_t   flagWiFiFail:1; // WiFi断开连接
    uint8_t   flagSelfTest:1;

    char      wifiSSID[34];
    char      wifiPass[34];

    char      cloudHost[36];
    uint16_t  cloudPort;
    char      cloudUpdateUrl[64];
    char      cloudFwCheckUrl[64];
} __attribute__((packed));

//ConfigStore configStore;

const ConfigStore configDefault = {
    0x26512E6D,  //0x265CAE6D
    "0.0.1",
    0, 0, 0, 0,
    "",
    "",    
    "192.168.1.108",
    6051,
    "/firmware/esp8266",
    "/hasNewfirmware/"
};

// typedef struct{
//     const char* ssid;
//     const char* passwd;
// }netConfig;

// const netConfig netconfig = {"......", "......"};

boolean initConfig(ConfigStore &configStore);

// 将配置写入flash
void writeConfig(ConfigStore &configStore);

// 从flash读取配置
boolean readConfig(ConfigStore &configStore);

void connectWiFi(ConfigStore &configStore);

void monitorWiFi(ConfigStore &configStore);

// 通过Smart Config获取密码
void smartConfig(ConfigStore &configStore);

// 固件升级
void firmwareUpdate(ConfigStore &configStore);

// 检查固件升级信息
int checkFirmwareUpdate(ConfigStore &configStore);

// 
//void handleRoot();

#endif
