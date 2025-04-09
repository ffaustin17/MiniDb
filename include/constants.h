#pragma once

#include <stdint.h>

const int PAGE_SIZE = 4096;
const int RECORD_SIZE = sizeof(uint32_t) + 128;
const int RECORDS_PER_PAGE = PAGE_SIZE / RECORD_SIZE;