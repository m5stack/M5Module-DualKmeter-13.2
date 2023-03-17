#ifndef __MODULE_DUALKMETER_H
#define __MODULE_DUALKMETER_H

#include "Arduino.h"
#include "Wire.h"

#define DUALKMETER_ADDR                                0x11
#define DUALKMETER_TEMP_VAL_REG                        0x00
#define DUALKMETER_INTERNAL_TEMP_VAL_REG               0x10
#define DUALKMETER_KMETER_SEL_REG                      0x20
#define DUALKMETER_KMETER_ERROR_STATUS_REG             0x30
#define DUALKMETER_TEMP_CELSIUS_STRING_REG             0x40
#define DUALKMETER_TEMP_FAHRENHEIT_STRING_REG          0x50
#define DUALKMETER_INTERNAL_TEMP_CELSIUS_STRING_REG    0x60
#define DUALKMETER_INTERNAL_TEMP_FAHRENHEIT_STRING_REG 0x70
#define DUALKMETER_FIRMWARE_VERSION_REG                0xFE

class MODULE_DUALKMETER {
   private:
    uint8_t _addr;
    TwoWire *_wire;
    uint8_t _scl;
    uint8_t _sda;
    uint8_t _speed;
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    void writeBytes(uint8_t addr, uint8_t reg, int8_t *buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, int8_t *buffer, uint8_t length);

   public:
    bool begin(TwoWire *wire = &Wire, uint8_t addr = DUALKMETER_ADDR,
               uint8_t sda = 21, uint8_t scl = 22, uint32_t speed = 100000L);
    void setKmeter(uint8_t k_sel);
    int32_t getCelsiusTempValue(void);
    int32_t getFahrenheitTempValue(void);
    int32_t getInternalCelsiusTempValue(void);
    int32_t getInternalFahrenheitTempValue(void);
    uint8_t getReadyStatus(void);
    void getCelsiusTempString(char *str);
    void getFahrenheitTempString(char *str);
    void getInternalCelsiusTempString(char *str);
    void getInternalFahrenheitTempString(char *str);
    uint8_t getFirmwareVersion(void);
};

#endif
