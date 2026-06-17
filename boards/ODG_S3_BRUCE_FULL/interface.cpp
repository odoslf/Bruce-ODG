#include "core/powerSave.h"
#include "core/utils.h"
#include <Arduino.h>
#include <Wire.h>
#include <interface.h>
#include "CYD28_TouchscreenR.h"

#define CYD28_DISPLAY_HOR_RES_MAX 320
#define CYD28_DISPLAY_VER_RES_MAX 240

CYD28_TouchR touch(CYD28_DISPLAY_HOR_RES_MAX, CYD28_DISPLAY_VER_RES_MAX);

#define XPT2046_CS XPT2046_SPI_CONFIG_CS_GPIO_NUM

static void odgLockHardwareDefaults() {
#if defined(SDCARD_SCK)
bruceConfigPins.SDCARD_bus.sck = (gpio_num_t)SDCARD_SCK;
bruceConfigPins.SDCARD_bus.miso = (gpio_num_t)SDCARD_MISO;
bruceConfigPins.SDCARD_bus.mosi = (gpio_num_t)SDCARD_MOSI;
bruceConfigPins.SDCARD_bus.cs = (gpio_num_t)SDCARD_CS;
#endif

#if defined(USE_CC1101_VIA_SPI)
bruceConfigPins.rfModule = CC1101_SPI_MODULE;
bruceConfigPins.rfFreq = 433.92f;
bruceConfigPins.CC1101_bus.sck = (gpio_num_t)CC1101_SCK_PIN;
bruceConfigPins.CC1101_bus.miso = (gpio_num_t)CC1101_MISO_PIN;
bruceConfigPins.CC1101_bus.mosi = (gpio_num_t)CC1101_MOSI_PIN;
bruceConfigPins.CC1101_bus.cs = (gpio_num_t)CC1101_SS_PIN;
bruceConfigPins.CC1101_bus.io0 = (gpio_num_t)CC1101_GDO0_PIN;
bruceConfigPins.CC1101_bus.io2 = (gpio_num_t)CC1101_GDO2_PIN;
#endif

#if defined(USE_NRF24_VIA_SPI)
bruceConfigPins.NRF24_bus.sck = (gpio_num_t)NRF24_SCK_PIN;
bruceConfigPins.NRF24_bus.miso = (gpio_num_t)NRF24_MISO_PIN;
bruceConfigPins.NRF24_bus.mosi = (gpio_num_t)NRF24_MOSI_PIN;
bruceConfigPins.NRF24_bus.cs = (gpio_num_t)NRF24_SS_PIN;
bruceConfigPins.NRF24_bus.io0 = (gpio_num_t)NRF24_CE_PIN;
bruceConfigPins.NRF24_bus.io2 = GPIO_NUM_NC;
#endif

#if !defined(LITE_VERSION) && defined(LORA_SCK)
bruceConfigPins.LoRa_bus.sck = (gpio_num_t)LORA_SCK;
bruceConfigPins.LoRa_bus.miso = (gpio_num_t)LORA_MISO;
bruceConfigPins.LoRa_bus.mosi = (gpio_num_t)LORA_MOSI;
bruceConfigPins.LoRa_bus.cs = (gpio_num_t)LORA_CS;
bruceConfigPins.LoRa_bus.io0 = (gpio_num_t)LORA_RST;
bruceConfigPins.LoRa_bus.io2 = (gpio_num_t)LORA_DIO0;
#endif

#if defined(GROVE_SDA) && defined(GROVE_SCL)
bruceConfigPins.i2c_bus.sda = (gpio_num_t)GROVE_SDA;
bruceConfigPins.i2c_bus.scl = (gpio_num_t)GROVE_SCL;
bruceConfigPins.rfidModule = PN532_I2C_MODULE;
#endif

#if defined(IR_TX_PINS)
bruceConfigPins.irTx = 4;
#endif

#if defined(IR_RX_PINS)
bruceConfigPins.irRx = 5;
#endif
}

/***************************************************************************************
** Function name: _setup_gpio()
** Location: main.cpp
** Description:   initial setup for the device
***************************************************************************************/
void _setup_gpio() {
    odgLockHardwareDefaults();

    pinMode(XPT2046_CS, OUTPUT);
    digitalWrite(XPT2046_CS, HIGH);

#if defined(SDCARD_CS) && (SDCARD_CS >= 0)
    pinMode(SDCARD_CS, OUTPUT);
    digitalWrite(SDCARD_CS, HIGH);
#endif

#if defined(USE_CC1101_VIA_SPI)
    pinMode(CC1101_SS_PIN, OUTPUT);
    digitalWrite(CC1101_SS_PIN, HIGH);
    pinMode(CC1101_GDO0_PIN, INPUT);
#endif

#if defined(USE_NRF24_VIA_SPI)
    pinMode(NRF24_SS_PIN, OUTPUT);
    digitalWrite(NRF24_SS_PIN, HIGH);
    pinMode(NRF24_CE_PIN, OUTPUT);
    digitalWrite(NRF24_CE_PIN, LOW);
#endif

#if defined(LORA_CS)
    pinMode(LORA_CS, OUTPUT);
    digitalWrite(LORA_CS, HIGH);
#endif

#if defined(LORA_RST)
    pinMode(LORA_RST, OUTPUT);
    digitalWrite(LORA_RST, HIGH);
#endif

#if defined(LORA_DIO0)
    pinMode(LORA_DIO0, INPUT);
#endif

#if defined(LORA_BUSY)
    pinMode(LORA_BUSY, INPUT);
#endif

#if defined(GROVE_SDA) && defined(GROVE_SCL)
    Wire.begin(GROVE_SDA, GROVE_SCL);
#endif

#if defined(IR_TX_PINS)
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
#endif

#if defined(IR_RX_PINS)
    pinMode(5, INPUT);
#endif

    if (!touch.begin()) {
        Serial.println("Touch IC not Started");
        log_i("Touch IC not Started");
    } else {
        log_i("Touch IC Started");
    }

    bruceConfig.colorInverted = 0;
    bruceConfig.startupApp = "WebUI";
}

void _post_setup_gpio() {
odgLockHardwareDefaults();

#if defined(SDCARD_CS) && (SDCARD_CS >= 0)
pinMode(SDCARD_CS, OUTPUT);
digitalWrite(SDCARD_CS, HIGH);
#endif

#if defined(USE_CC1101_VIA_SPI)
pinMode(CC1101_SS_PIN, OUTPUT);
digitalWrite(CC1101_SS_PIN, HIGH);
pinMode(CC1101_GDO0_PIN, INPUT);
#endif

#if defined(USE_NRF24_VIA_SPI)
pinMode(NRF24_SS_PIN, OUTPUT);
digitalWrite(NRF24_SS_PIN, HIGH);
pinMode(NRF24_CE_PIN, OUTPUT);
digitalWrite(NRF24_CE_PIN, LOW);
#endif

#if defined(LORA_CS)
pinMode(LORA_CS, OUTPUT);
digitalWrite(LORA_CS, HIGH);
#endif

#if defined(LORA_RST)
pinMode(LORA_RST, OUTPUT);
digitalWrite(LORA_RST, HIGH);
#endif

#if defined(LORA_DIO0)
pinMode(LORA_DIO0, INPUT);
#endif

#if defined(LORA_BUSY)
pinMode(LORA_BUSY, INPUT);
#endif

#if defined(IR_TX_PINS)
pinMode(4, OUTPUT);
digitalWrite(4, LOW);
#endif

#if defined(IR_RX_PINS)
pinMode(5, INPUT);
#endif
}

/***************************************************************************************
** Function name: getBattery()
** location: display.cpp
** Description:   Delivers the battery value from 1-100
***************************************************************************************/
int getBattery() { return 0; }

/***************************************************************************************
** Function name: isCharging()
** Description:   Default implementation that returns false
***************************************************************************************/
bool isCharging() { return false; }

/*********************************************************************
** Function: setBrightness
** location: settings.cpp
** set brightness value
**********************************************************************/
void _setBrightness(uint8_t brightval) { (void)brightval; }

/*********************************************************************
** Function: InputHandler
** Handles the variables PrevPress, NextPress, SelPress, AnyKeyPress and EscPress
**********************************************************************/
void InputHandler(void) {
    static long d_tmp = 0;
    if (millis() - d_tmp > 200 || LongPress) {
        if (touch.touched()) {
            auto t = touch.getPointScaled();

            if (bruceConfigPins.rotation == 3) {
                t.y = (tftHeight + 20) - t.y;
                t.x = tftWidth - t.x;
            }
            if (bruceConfigPins.rotation == 0) {
                int tmp = t.x;
                t.x = tftWidth - t.y;
                t.y = tmp;
            }
            if (bruceConfigPins.rotation == 2) {
                int tmp = t.x;
                t.x = t.y;
                t.y = (tftHeight + 20) - tmp;
            }

            if (!wakeUpScreen()) AnyKeyPress = true;
            else goto END;

            touchPoint.x = t.x;
            touchPoint.y = t.y;
            touchPoint.pressed = true;
            touchHeatMap(touchPoint);
        END:
            d_tmp = millis();
        }
    }
}

/*********************************************************************
** Function: powerOff
** location: mykeyboard.cpp
** Turns off the device (or try to)
**********************************************************************/
void powerOff() {}

/*********************************************************************
** Function: checkReboot
** location: mykeyboard.cpp
** Btn logic to turnoff the device (name is odd btw)
**********************************************************************/
void checkReboot() {}
