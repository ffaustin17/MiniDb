#pragma once
#include "page.h"
#include <fstream>
#include <string>

class Pager{
    public:
        Pager(const std::string& filename);

        ~Pager();

        void writePage(int pageIndex, const Page& page);

        Page readPage(int pageIndex);

    private:
        std::fstream file;
};