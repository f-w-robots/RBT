#include <Arduino.h>
#include <EEPROM.h>
#include "Config.h"

int8_t Config::_sensorCount = -1;

uint8_t Config::sensorCount() {
  if (_sensorCount < 0)
    _sensorCount = EEPROM.read(0);
  return _sensorCount;
}

void Config::sensorCount(int8_t count) {
  _sensorCount = count;
  EEPROM.write(0, _sensorCount);
}

void Config::writeDonwSensor(uint8_t number, uint16_t value) {
  EEPROM.write(1 + sensorCount() + sensorCount() + number + number, value & 0xFF);
  EEPROM.write(1 + sensorCount() + sensorCount() + number + number + 1, (value >> 8) & 0xFF);
}

void Config::writeUpSensor(uint8_t number, uint16_t value) {
  EEPROM.write(1 + number + number, value & 0xFF);
  EEPROM.write(1 + number + number + 1, (value >> 8) & 0xFF);
}

uint16_t Config::readDonwSensor(uint8_t number) {
  return ((EEPROM.read(1 + sensorCount() + sensorCount() + number + number) << 0) & 0xFF) +
         ((EEPROM.read(1 + sensorCount() + sensorCount() + number + number + 1) << 8) & 0xFFFF);
}

uint16_t Config::readUpSensor(uint8_t number) {
  return ((EEPROM.read(1 + number + number) << 0) & 0xFF) +
         ((EEPROM.read(1 + number + number + 1) << 8) & 0xFFFF);
}

