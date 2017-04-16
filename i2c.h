#pragma once

#include <cstdint>

class I2C
{
public:
    I2C(uint8_t address);
    ~I2C();

    uint16_t read(uint8_t addr);
    void write(uint8_t addr, uint16_t data);
private:
    const uint8_t address;
    int file;
};
