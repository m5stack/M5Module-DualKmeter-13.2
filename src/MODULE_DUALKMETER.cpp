#include "MODULE_DUALKMETER.h"
#include <string.h>

void MODULE_DUALKMETER::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                                   uint8_t length) {
    _wire->beginTransmission(addr);
    _wire->write(reg);
    for (int i = 0; i < length; i++) {
        _wire->write(*(buffer + i));
    }
    _wire->endTransmission();
}

void MODULE_DUALKMETER::writeBytes(uint8_t addr, uint8_t reg, int8_t *buffer,
                                   uint8_t length) {
    _wire->beginTransmission(addr);
    _wire->write(reg);
    for (int i = 0; i < length; i++) {
        _wire->write(*(buffer + i));
    }
    _wire->endTransmission();
}

void MODULE_DUALKMETER::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                                  uint8_t length) {
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission(false);
    _wire->requestFrom(addr, length);
    for (int i = 0; i < length; i++) {
        buffer[index++] = _wire->read();
    }
}

void MODULE_DUALKMETER::readBytes(uint8_t addr, uint8_t reg, int8_t *buffer,
                                  uint8_t length) {
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission(false);
    _wire->requestFrom(addr, length);
    for (int i = 0; i < length; i++) {
        buffer[index++] = _wire->read();
    }
}

bool MODULE_DUALKMETER::begin(TwoWire *wire, uint8_t addr, uint8_t sda,
                              uint8_t scl, uint32_t speed) {
    _wire  = wire;
    _addr  = addr;
    _sda   = sda;
    _scl   = scl;
    _speed = speed;
    _wire->begin(_sda, _scl, _speed);
    delay(10);
    _wire->beginTransmission(_addr);
    uint8_t error = _wire->endTransmission();
    if (error == 0) {
        return true;
    } else {
        return false;
    }
}

void MODULE_DUALKMETER::setKmeter(uint8_t k_sel) {
    writeBytes(_addr, DUALKMETER_KMETER_SEL_REG, &k_sel, 1);
}

int32_t MODULE_DUALKMETER::getCelsiusTempValue(void) {
    uint8_t read_buf[4] = {0};

    readBytes(_addr, DUALKMETER_TEMP_VAL_REG, read_buf, 4);
    return (read_buf[3] << 24) | (read_buf[2] << 16) | (read_buf[1] << 8) |
           read_buf[0];
}

int32_t MODULE_DUALKMETER::getFahrenheitTempValue(void) {
    uint8_t read_buf[4] = {0};

    readBytes(_addr, DUALKMETER_TEMP_VAL_REG + 4, read_buf, 4);
    return (read_buf[3] << 24) | (read_buf[2] << 16) | (read_buf[1] << 8) |
           read_buf[0];
}

int32_t MODULE_DUALKMETER::getInternalCelsiusTempValue(void) {
    uint8_t read_buf[4] = {0};

    readBytes(_addr, DUALKMETER_INTERNAL_TEMP_VAL_REG, read_buf, 4);
    return (read_buf[3] << 24) | (read_buf[2] << 16) | (read_buf[1] << 8) |
           read_buf[0];
}

int32_t MODULE_DUALKMETER::getInternalFahrenheitTempValue(void) {
    uint8_t read_buf[4] = {0};

    readBytes(_addr, DUALKMETER_INTERNAL_TEMP_VAL_REG + 4, read_buf, 4);
    return (read_buf[3] << 24) | (read_buf[2] << 16) | (read_buf[1] << 8) |
           read_buf[0];
}

void MODULE_DUALKMETER::getCelsiusTempString(char *str) {
    char read_buf[8] = {0};

    readBytes(_addr, DUALKMETER_TEMP_CELSIUS_STRING_REG, (uint8_t *)read_buf,
              8);
    memcpy(str, read_buf, sizeof(read_buf));
}

void MODULE_DUALKMETER::getFahrenheitTempString(char *str) {
    uint8_t read_buf[8] = {0};

    readBytes(_addr, DUALKMETER_TEMP_FAHRENHEIT_STRING_REG, (uint8_t *)read_buf,
              8);
    memcpy(str, read_buf, sizeof(read_buf));
}

void MODULE_DUALKMETER::getInternalCelsiusTempString(char *str) {
    uint8_t read_buf[8] = {0};

    readBytes(_addr, DUALKMETER_INTERNAL_TEMP_CELSIUS_STRING_REG,
              (uint8_t *)read_buf, 8);
    memcpy(str, read_buf, sizeof(read_buf));
}

void MODULE_DUALKMETER::getInternalFahrenheitTempString(char *str) {
    uint8_t read_buf[8] = {0};

    readBytes(_addr, DUALKMETER_INTERNAL_TEMP_FAHRENHEIT_STRING_REG,
              (uint8_t *)read_buf, 8);
    memcpy(str, read_buf, sizeof(read_buf));
}

uint8_t MODULE_DUALKMETER::getReadyStatus(void) {
    uint8_t read_buf[4] = {0};

    readBytes(_addr, DUALKMETER_KMETER_ERROR_STATUS_REG, read_buf, 1);
    return read_buf[0];
}

uint8_t MODULE_DUALKMETER::getFirmwareVersion(void) {
    uint8_t reg;
    uint8_t read_buf[4] = {0};

    readBytes(_addr, DUALKMETER_FIRMWARE_VERSION_REG, read_buf, 1);
    return read_buf[0];
}
