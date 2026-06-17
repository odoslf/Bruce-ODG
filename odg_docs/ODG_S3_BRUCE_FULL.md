# ODG_S3_BRUCE_FULL

- BASE_REF: ODG_S3_BRUCE_FULL v2.0
- Estado R1: BOARD_PROFILE_BOOT
- Repo/rama: odg-s3-bruce-full

## Estado de R1

Este perfil mínimo está preparado solo para compilar `pio run -e ODG_S3_BRUCE_FULL` en Bruce sobre ESP32-S3 N16R8. En R1 no se activa hardware externo real.

## Pinout final previsto completo para fases futuras

> Todo este pinout está previsto para fases futuras; R1 solo define buses base y mantiene módulos externos desactivados.

| Función prevista | GPIO |
| --- | ---: |
| UART TX | 43 |
| UART RX | 44 |
| Grove SDA / I2C SDA | 15 |
| Grove SCL / I2C SCL | 16 |
| SPI SS base | 10 |
| SPI MOSI base | 11 |
| SPI SCK base | 12 |
| SPI MISO base | 13 |
| RGB LED integrado | 48 |
| microSD SCK futura | 3 |
| microSD MOSI futura | 45 |
| microSD MISO futura | 46 |
| microSD CS futura | 8 |
| TFT real futuro | Por definir en fase posterior |
| Touch real futuro | Por definir en fase posterior |
| CC1101 futuro | Por definir en fase posterior |
| nRF24 futuro | Por definir en fase posterior |
| SX1262 futuro | Por definir en fase posterior |
| PN532 futuro | Por definir en fase posterior |
| IR futuro | Por definir en fase posterior |

## Módulos NO activados en R1

- TFT real
- Touch
- SD
- CC1101
- nRF24
- SX1262
- PN532
- IR

## Nota SD

La microSD de la TFT no viene conectada de fábrica al shield. Se puenteará manualmente en R4: SD_SCK GPIO3, SD_MOSI GPIO45, SD_MISO GPIO46, SD_CS GPIO8.

GPIO8 es CS elegido por diseño para SD, no pin SD de fábrica.

## R2 — DISPLAY_OK

Estado: TFT activada por build flags.

Pines:

| Señal TFT | GPIO |
| --- | ---: |
| TFT_CS | GPIO14 |
| TFT_RST | GPIO21 |
| TFT_DC | GPIO47 |
| TFT_MOSI | GPIO45 |
| TFT_SCLK | GPIO3 |
| TFT_MISO | GPIO46 |
| TFT_BL | -1 |

Touch: pendiente R3.

SD: pendiente R4.

Módulos externos: pendientes R6-R10.

Si la pantalla sale blanca/negra/colores mal, la siguiente micro-ronda probará "ILI9341_2_DRIVER" o rotación. No cambiar pines en R2.

## R3 — TOUCH_OK

Estado: Touch XPT2046 activado.

Pines:

| Señal touch | GPIO |
| --- | ---: |
| TOUCH_CLK | GPIO42 |
| TOUCH_DIN | GPIO2 |
| TOUCH_DO | GPIO41 |
| TOUCH_CS | GPIO1 |
| TOUCH_IRQ | -1 / NC |

Notas:

- Touch resistivo XPT2046 por librería interna CYD28_TouchR.
- No se usa USE_TFT_eSPI_TOUCH.
- No se usa GT911.
- Sin botones físicos.
- Si el touch responde girado o invertido, la siguiente micro-ronda ajustará rotación/calibración en interface.cpp sin cambiar pines.
- OLED/DHT11/POT del shield siguen fuera por conflicto con touch.

SD pendiente R4.

SD será puente manual:

| Señal SD futura | GPIO |
| --- | ---: |
| SD_SCK | GPIO3 |
| SD_MOSI | GPIO45 |
| SD_MISO | GPIO46 |
| SD_CS | GPIO8 |

## R4 — SD_OK

Estado: microSD activada por build flags.

Tipo: SD_TFT_MANUAL_BRIDGE_SPI.

La SD se puentea manualmente desde los pads traseros de la TFT.
No viene conectada de fábrica al shield.
No usa el conector OLED.
Comparte bus SPI con la TFT.

Pinout:

| Señal SD | GPIO |
| --- | ---: |
| SD_SCK | GPIO3 |
| SD_MOSI | GPIO45 |
| SD_MISO | GPIO46 |
| SD_CS | GPIO8 |

Notas:

- GPIO8 es CS elegido por diseño.
- TFT_CS GPIO14 y SD_CS GPIO8 deben reposar HIGH.
- Si la SD no monta en prueba real, revisar primero cableado de SD_CS/GPIO8 y puentes de SD_SCK/SD_MOSI/SD_MISO.
- No cambiar pines TFT ni touch por un fallo de SD.
- CC1101/nRF24/SX1262/PN532/IR siguen pendientes y apagados.

## R5 — WEBUI_USB_BLE_BASELINE

Estado:
Baseline de control cerrada.

Control principal:
Pantalla + touch.

Control secundario:
WebUI Bruce mediante WiFi interno ESP32-S3.

USB:
USB HID nativo queda declarado por "-DUSB_as_HID=1".
GPIO19/GPIO20 quedan reservados para USB D-/D+.
No usar GPIO19/GPIO20 para módulos.

WiFi:
Se usa únicamente el WiFi interno de la ESP32-S3.
No hay WiFi externo.
No hay ESP8266/ESP32 externo.

BLE:
BLE interno de la ESP32-S3 queda disponible.
No se activa Bluetooth Classic.
No se activa A2DP.
No se usa ESP32 Classic.

Estado hardware tras R5:
TFT: activa.
Touch: activo.
SD: activa por flags, pendiente de prueba física cuando esté puenteada.
CC1101: apagado, pendiente R6.
nRF24: apagado, pendiente R7.
SX1262: apagado, pendiente R8.
PN532: apagado, pendiente R9.
IR: apagado, pendiente R10.

## R6 — CC1101_433_OK

CC1101 433 MHz activado por SPI.

Pinout:
SCK GPIO12
MOSI GPIO11
MISO GPIO13
CSN GPIO39
GDO0 GPIO40
GDO2 NC

Notas:
CC1101 comparte el bus SPI base GPIO12/GPIO11/GPIO13.
CS propio GPIO39.
GDO0 GPIO40.
GDO2 no conectado.

## R7 — NRF24_OK

nRF24L01+ PA/LNA activado por SPI.

Pinout:
SCK GPIO12
MOSI GPIO11
MISO GPIO13
CE GPIO6
CSN GPIO7

Notas:
nRF24 comparte el bus SPI base GPIO12/GPIO11/GPIO13.
CSN propio GPIO7.
CE GPIO6.
Durante setup CSN queda HIGH y CE queda LOW.

## R8 — LORA_SX1262_OK

SX1262 LoRa 868 LR30 activado.

Pinout:
SCK GPIO12
MOSI GPIO11
MISO GPIO13
CS GPIO10
DIO1/IRQ GPIO17
RST GPIO18
BUSY GPIO9

Notas:
El código ODG arranca LoRa como SX1262 por defecto.
El fichero inicial lora_settings.json se crea con LoRa_Radio SX1262 y frecuencia 868100000.00.
LoRa comparte el bus SPI base GPIO12/GPIO11/GPIO13.
CS propio GPIO10.
DIO1 físico se mapea como LORA_DIO0 GPIO17.
BUSY GPIO9.

## R9 — PN532_I2C_OK

PN532 V3 activado como módulo RFID/NFC por defecto en modo I2C.

Pinout:
SDA GPIO15
SCL GPIO16

Notas:
PN532 usa el bus I2C GROVE_SDA/GROVE_SCL.
PN532 no usa SPI en este perfil.
El perfil fija bruceConfigPins.rfidModule = PN532_I2C_MODULE.
El código no inicializa manualmente el PN532; Bruce lo inicializa desde su módulo RFID.

## R10 — IR_OK

KY-005 IR TX y KY-022 IR RX activados.

Pinout:
KY-005 SIGNAL GPIO4
KY-022 SIGNAL GPIO5

Notas:
IR TX queda disponible como ODG KY-005 TX GPIO4.
IR RX queda disponible como ODG KY-022 RX GPIO5.
Durante setup GPIO4 queda OUTPUT LOW.
Durante setup GPIO5 queda INPUT.
