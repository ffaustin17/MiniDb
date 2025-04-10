#include <iostream>
#include <cstring>
#include "storage_engine.h"

/**
 * @brief Constructs the StorageEngine and loads existing data from disk.
 * 
 * Iterates through all non-empty pages to compute totalRecords.
 * Ensures newly added records don't overwrite existing ones.
 * 
 * @param filename Path to the backing database file.
 */
StorageEngine::StorageEngine(const std::string& filename) : pager(filename)
{
    //scan all pages to determine how many records exist
    totalRecords = 0;
    int pageIndex = 0;

    while(true){
        Page page = pager.readPage(pageIndex);

        if(page.numRecords == 0) break;

        totalRecords += page.numRecords;
        pageIndex++;
    }
}


/**
 * @brief Inserts a new key-value record into the storage engine.abort
 * 
 * The eninge uses page-based storage. This method calculates the correct
 * page and offset, inserts the record, and writes it back to disk via the pager.
 * 
 * @param key The unique integer key of the record
 * @param value The string value to associate with the key.
 */
void StorageEngine::put(uint32_t key, const std::string& value){
    int pageIndex = totalRecords / RECORDS_PER_PAGE;
    int offset = totalRecords % RECORDS_PER_PAGE;

    Page page = pager.readPage(pageIndex);

    if(page.numRecords >= RECORDS_PER_PAGE){
        std::cerr << "Error: Page is full. This shouldn't happen!" << std::endl;
        return;
    }

    Record record;

    record.key = key;

    std::strncpy(record.value, value.c_str(), sizeof(record.value));
    record.value[sizeof(record.value) - 1] = '\0'; //ensure null-termination

    page.records[offset] = record;
    page.numRecords++;

    pager.writePage(pageIndex, page);
    totalRecords++;
}

/**
 * @brief Searches for a record by key and retrieves it
 * 
 * Performs a linear scan of all pages until the matching key is
 * found. The result is returned in outRecord. 
 * 
 * @param key The key to search for
 * @param outRecord Output parameter for the matched record (if found)
 * @return true if found, false otherwise.
 */
bool StorageEngine::get(uint32_t key, Record& outRecord){
    int pageCount = (totalRecords + RECORDS_PER_PAGE - 1) / RECORDS_PER_PAGE;

    for(int i = 0; i < pageCount; i++){
        Page page = pager.readPage(i);

        for(int j = 0; j < page.numRecords; ++j){
            if(page.records[j].key == key){
                outRecord = page.records[j];
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Outputs all key-value records stored in the engine.
 * 
 * Reads each page and prints the records in insertion order.
 */
void StorageEngine::scan(){
    int pageCount = (totalRecords + RECORDS_PER_PAGE - 1) / RECORDS_PER_PAGE;

    for(int i = 0; i < pageCount; i++){
        Page page = pager.readPage(i);

        for(int j = 0; j < page.numRecords; ++j){
            Record& rec = page.records[j];
            std::cout << "[" << rec.key << "] => " << rec.value << std::endl;
        }
    }
}