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

    void show_thread();

private:
    //数据生成线程
    pthread_t data_generate_thread_;
    //数据删除线程
    pthread_t data_remove_thread_;
    //目录管理器
    CatalogManager *catalog_manager_;
    //内存管理器
    MemoryManager *memory_manager_;
    //空闲的执行线程队列
    std::list<int> free_thread_list_;
    //已运行的执行线程队列
    std::list<FileThread *> alloc_thread_list_;
};


#endif //OSMANAGER_THREADMANAGER_H
