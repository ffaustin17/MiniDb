#pragma once

#include "pager.h"
#include "record.h"

class StorageEngine{
    private:
        Pager pager;
        int totalRecords = 0;

        int findRecordPage(uint32_t key, int& outIndexInPage);
    public:
        StorageEngine(const std::string& filename);

        void put(uint32_t key, const std::string& value);
        bool get(uint32_t key, Record& outRecord);
        void scan();
};