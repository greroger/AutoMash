#include <iostream>
#include <iomanip>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>

#include "i2c.h"

using namespace std;

I2C::I2C(uint8_t address)
: address(address)
{
    file = open("/dev/i2c-1", O_RDWR);

    if (file < 0) {
        perror("open");
        exit(1);
    }

    if (ioctl(file, I2C_SLAVE, address) < 0) {
        perror("ioctl");
        exit(1);
    }
}

I2C::~I2C()
{
    close(file);
}

uint16_t I2C::read(uint8_t addr)
{
    cout << __PRETTY_FUNCTION__ << ": " << (int)addr << endl;
    int32_t res = i2c_smbus_read_word_data(file, addr);
    if (res < 0) {
        perror("i2c_smbus_read_word_data");
        exit(1);
    }
    return res & 0xffff;
}

void I2C::write(uint8_t addr, uint16_t data)
{
}

