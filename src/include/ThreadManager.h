//
// Created by 86183 on 2022/12/24.
//

#ifndef OSMANAGER_THREADMANAGER_H
#define OSMANAGER_THREADMANAGER_H


#include <thread>
#include "DiskManager.h"
#include "CatalogManager.h"
#include "MemoryManager.h"

class ThreadManager {
public:
    //构造函数根据自身情况添加参数
    ThreadManager(DiskManager *disk_manager, CatalogManager *catalog_manager);

    ~ThreadManager() = default;

    //提供给用户的数据生成接口
    void create(std::string name, std::string path, std::string data);

    //提供给用户的数据删除接口
    void remove(std::string name, std::string path);

private:
    std::thread data_genethread_;
    std::thread data_thread_;
    DiskManager *disk_manager_;
    CatalogManager *catalog_manager_;
    MemoryManager *memory_manager_;


    //数据生成
    void data_create_task(std::string name, std::string path, std::string data);

    //删除数据
    void data_delete_task(std::string name, std::string path);

    //将文件数据从外存调入内存
    void data_call_task(std::string name, std::string path);
};


#endif //OSMANAGER_THREADMANAGER_H
