//
// Created by 86183 on 2022/12/24.
//

#ifndef OSMANAGER_THREADMANAGER_H
#define OSMANAGER_THREADMANAGER_H


#include <thread>
#include "../disk/DiskManager.h"
#include "../catalog/CatalogManager.h"
#include "../memory/MemoryManager.h"
#include <pthread.h>

class ThreadManager {
public:
    //构造函数根据自身情况添加参数
    ThreadManager(CatalogManager *catalog_manager, MemoryManager *memory_manager);

    ~ThreadManager();

    //提供给用户的数据生成接口
    void create(std::string name, std::string data);

    //提供给用户的数据删除接口
    void remove(std::string name);

    //提供给用户的打开文件
    void open(std::string name);

private:
    pthread_t data_generate_thread_;
    pthread_t data_remove_thread_;
    CatalogManager *catalog_manager_;
    MemoryManager *memory_manager_;

    //空闲的执行线程队列
    std::list<pthread_t> free_thread_list_;
    //已运行的执行线程队列
    std::list<FileThread> alloc_thread_list_;
};


#endif //OSMANAGER_THREADMANAGER_H
