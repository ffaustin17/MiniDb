#pragma once
#include "page.h"
#include <fstream>
#include <string>

/**
 * @brief Pager handles low-level file I/O for reading and writing full pages (4KB blocks)
 * to and from a binary storage file.
 */
class Pager{
    public:
        /**
         * @brief Opens the file (or creates it if not found) for reading/writing pages.
         */
        Pager(const std::string& filename);

        /**
         * @brief Ensures the file is closed properly on destruction
         */
        ~Pager();

        /**
         * @brief Writes a full page to the file at the given index.
         */
        void writePage(int pageIndex, const Page& page);

        /**
         * @brief Reads a full page from the file at the given page index.
         */
        Page readPage(int pageIndex);

    private:
        std::fstream file; // File stream for binary I/O
};