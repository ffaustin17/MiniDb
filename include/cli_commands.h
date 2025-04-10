#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <sstream>
#include <iostream>
#include "storage_engine.h"

inline std::unordered_map<std::string, std::function<void(std::istringstream&)>>
setupCommands(StorageEngine& db){
    std::unordered_map<std::string, std::function<void(std::istringstream&)>> commands;

    commands["put"] = [&](std::istringstream& iss){
        uint32_t key;
        std::string value;
        if(iss >> key >> value){
            db.put(key, value);
            std::cout << "Inserted key = " << key << ", value = \"" << value << "\"" << std::endl;
        }
        else{
            std::cout << "Usage: put <key> <value>" << std::endl;
        }
    };

    commands["get"] = [&](std::istringstream& iss) {
        uint32_t key;
        if (iss >> key) {
            Record r;
            if (db.get(key, r)) {
                std::cout << "Found: [" << r.key << "] => " << r.value << std::endl;
            } else {
                std::cout << "Key not found." << std::endl;
            }
        } else {
            std::cout << "Usage: get <key>" << std::endl;
        }
    };

    commands["scan"] = [&](std::istringstream&) {
        db.scan();
    };

    commands["exit"] = [&](std::istringstream&) {
        std::cout << "Goodbye!" << std::endl;
        std::exit(0);
    };

    return commands;
}