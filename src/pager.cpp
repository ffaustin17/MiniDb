//this file implements how to:
// - Open the DB file (read/write)
// - Read a full page from the disk
// - Write a full page to the disk

#include "pager.h"
#include "page.h"
#include <iostream>
#include <cstring>

Pager::Pager(const std::string& filename){
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);

    //if the file doesn't exist, create it
    if(!file.is_open()){
        file.clear();
        file.open(filename, std::ios::out | std::ios::binary);
        file.close();
        file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    }

    if(!file.is_open()){
        std::cerr << "Failed to open or create file: " << filename << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

Pager::~Pager(){
    if(file.is_open()){
        file.close();
    }
}

Page Pager::readPage(int pageIndex){
    Page page;
    std::memset(&page, 0, sizeof(Page));

    file.seekg(pageIndex* PAGE_SIZE, std::ios::beg);

    if(!file.read(reinterpret_cast<char*>(&page), sizeof(Page))){
        //no error unless it's NOT the first read (in the case that we are reading an empty new file)
        if(!file.eof()){
            std::cerr << "Failed to read page at index " << pageIndex << std::endl;
        }
    }

    return page;
}

void Pager::writePage(int pageIndex, const Page& page){
    file.seekp(pageIndex * PAGE_SIZE, std::ios::beg);

    if(!file.write(reinterpret_cast<const char*>(&page), sizeof(Page))){
        std::cerr << "Failed to write page at index " << pageIndex << std::endl;
    }

    file.flush(); //ensure we write to disk immediately.
}