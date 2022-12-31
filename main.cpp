#include <iostream>
#include "src/kernel/disk/DiskManager.h"
#include "src/kernel/catalog/CatalogManager.h"
#include "src/kernel/thread/ThreadManager.h"

void quick_test(ThreadManager *thread_manager) {
    for (int i = 0; i < 8; i++) {
        std::string name = "a" + std::to_string(i);
        thread_manager->open(name);
    }
}

void print_help() {
    std::cout << "命令说明-----------------" << std::endl;
    std::cout << "exit----------------退出" << std::endl;
    std::cout << "ls----------------列出当前目录所有文件/文件夹" << std::endl;
    std::cout << "cd----------------打开文件夹" << std::endl;
    std::cout << "mkdir----------------创建文件夹" << std::endl;
    std::cout << "rmdir----------------删除文件夹" << std::endl;
    std::cout << "create----------------创建文件" << std::endl;
    std::cout << "create test-----------一次性创建8个文件提供测试" << std::endl;
    std::cout << "open test-----------一次性打开8个文件提供测试" << std::endl;
    std::cout << "remove----------------删除文件" << std::endl;
    std::cout << "open------------------打开文件" << std::endl;
    std::cout << "show memory------------显示内存信息" << std::endl;
    std::cout << "show disk--------------显示外存信息" << std::endl;
    std::cout << "show thread------------显示线程信息" << std::endl;

}

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
        } else if (command == "help") {
            print_help();
        } else if (command == "ls") {
            catalog_manager->ls();
        } else if (command.substr(0, 5) == "mkdir") {
            catalog_manager->mkdir(command.substr(6, command.size() - 6));
        } else if (command.substr(0, 2) == "cd") {
            catalog_manager->cd(command.substr(3, command.size() - 3));
        } else if (command.substr(0, 5) == "rmdir") {
            catalog_manager->rmdir(command.substr(6, command.size() - 6));
        } else if (command == "create test") {
            catalog_manager->create_eight_files();
        } else if (command.substr(0, 6) == "create") {
            std::string file_name = command.substr(7, command.size() - 7);
            std::cout << "请输入文件内容" << std::endl;
            std::string file_data;
            getline(std::cin, file_data);
            thread_manager->create(file_name, file_data);

        } else if (command == "open test") {
            quick_test(thread_manager);
        } else if (command.substr(0, 4) == "open") {
            thread_manager->open(command.substr(5, command.size() - 5));

        } else if (command.substr(0, 6) == "remove") {
            thread_manager->remove(command.substr(7, command.size() - 7));
        } else if (command == "show memory") {
            memory_manager->show_memory();
        } else if (command == "show disk") {
            disk_manager->show_disk();
        } else if (command == "show thread") {
            thread_manager->show_thread();
        } else {
            std::cout << "不存在的命令，请重试" << std::endl;
        }
    }

    delete disk_manager;
    delete memory_manager;
    delete catalog_manager;
    delete thread_manager;
}
