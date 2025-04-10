#include <iostream>
#include <sstream>
#include <string>
#include "storage_engine.h"
#include "cli_commands.h"

int main(int argc, char* argv[]){
    std::string dbPath = (argc >= 3 && std::string(argv[1]) == "--db") ? argv[2] : "../data/store.db";
    StorageEngine db(dbPath);

    std::cout << "Simple DB Engine" << std::endl;
    std::cout << "Using DB file: " << dbPath << std::endl << std::endl;

    auto commands = setupCommands(db);

    std::string input;

    while(true){
        std::cout << "> ";
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::string command;
        iss >> command;

        if(auto it = commands.find(command); it != commands.end()){
            it -> second(iss);
        }
        else{
            std::cout << "Unknown command: " << command << std::endl;
        }
    }

    return 0;
}
