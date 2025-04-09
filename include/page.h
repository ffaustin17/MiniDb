#pragma once
#include "record.h"
#include "constants.h"

struct Page{
    Record records[RECORDS_PER_PAGE];  //should be 31 records per page since we are working with 4KB
    int numRecords = 0;                //tracks how many of these records are filled.
};