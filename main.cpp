#include <iostream>
#include "src/kernel/disk/DiskManager.h"
#include "src/kernel/catalog/CatalogManager.h"
#include "src/kernel/thread/ThreadManager.h"


int main() {
    DiskManager *disk_manager = new DiskManager();
    MemoryManager *memory_manager = new MemoryManager(disk_manager);
    CatalogManager *catalog_manager = new CatalogManager(disk_manager, memory_manager);
    ThreadManager *thread_manager = new ThreadManager(catalog_manager, memory_manager);

    while (true) {
        std::cout << path << ":";
        std::string command;
        getline(std::cin, command);

        if (command == "exit" || command == "quit") {
            break;
        } else if (command == "ls") {
            catalog_manager->ls();
        } else if (command.substr(0, 5) == "mkdir") {
            catalog_manager->mkdir(command.substr(6, command.size() - 6));
        } else if (command.substr(0, 2) == "cd") {
            catalog_manager->cd(command.substr(3, command.size() - 3));
        } else if (command.substr(0, 5) == "rmdir") {
            catalog_manager->rmdir(command.substr(6, command.size() - 6));
        } else if (command.substr(0, 6) == "create") {
            std::string file_name = command.substr(7, command.size() - 7);
            std::cout << "请输入文件内容" << std::endl;
            std::string file_data;
            getline(std::cin, file_data);
            thread_manager->create(file_name, file_data);

        } else if (command.substr(0, 4) == "open") {
            thread_manager->open(command.substr(5, command.size() - 5));

        } else if (command.substr(0, 6) == "remove") {
            thread_manager->remove(command.substr(7, command.size() - 7));
        } else if (command == "show memory") {

        } else if (command == "show disk") {

        } else if (command == "show thread") {

        }
    }

    delete disk_manager;
    delete memory_manager;
    delete catalog_manager;
    delete thread_manager;
}
