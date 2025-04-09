#pragma once

#include <stdint.h>

struct Record{
    uint32_t key;     //4 bytes
    char value[128];  //128 bytes ceiling
};