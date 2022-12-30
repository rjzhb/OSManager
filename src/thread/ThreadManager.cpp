//
// Created by 86183 on 2022/12/24.
//

#include <iostream>
#include "ThreadManager.h"

//互斥锁
static pthread_mutex_t mutex_A = PTHREAD_MUTEX_INITIALIZER;

struct CreateParam {
    std::string name;
    std::string data;
    CatalogManager *catalogManager;

    CreateParam(std::string name, std::string data, CatalogManager *catalogManager) {
        this->name = name;
        this->data = data;
        this->catalogManager = catalogManager;
    }
};

struct DeleteParam {
    std::string name;
    MemoryManager *memory_manager;
    CatalogManager *catalogManager;

    DeleteParam(std::string name, MemoryManager *memory_manager, CatalogManager *catalogManager) {
        this->name = name;
        this->memory_manager = memory_manager;
        this->catalogManager = catalogManager;
    }
};


static void *data_create_task(void *p) {
    pthread_mutex_lock(&mutex_A);
    CreateParam *param = reinterpret_cast<CreateParam *>(p);
    //调用目录管理功能建立目录项
    param->catalogManager->create_file(param->name, param->data);
    pthread_mutex_unlock(&mutex_A);
}


static void *data_delete_task(void *p) {
    pthread_mutex_lock(&mutex_A);
    DeleteParam *param = reinterpret_cast<DeleteParam *>(p);
    if (param->memory_manager->judge_memory(param->name)) {
        std::cout << "删除文件失败，该文件数据在内存中，需关闭后再试" << std::endl;
        return NULL;
    }
    //调用目录管理删除文件功能删除数据
    param->catalogManager->rmfile(param->name);
    pthread_mutex_unlock(&mutex_A);
}


static void *data_call_task(void *p) {
    pthread_mutex_lock(&mutex_A);
    using CallParam = DeleteParam;
    CallParam *param = reinterpret_cast<CallParam *>(p);
    if (param->memory_manager->judge_memory(param->name)) {
        std::cout << "打开文件失败，该文件正处于打开状态" << std::endl;
        return;
    }
    param->catalogManager->open(param->name);
    pthread_mutex_unlock(&mutex_A);
}


//下面是暴露给用户的接口

void ThreadManager::create(std::string name, std::string data) {
    CreateParam create_param(name, data, catalog_manager_);
    //开启用户创建线程
    pthread_create(&data_generate_thread_, NULL, &data_create_task, &create_param);
    pthread_join(data_generate_thread_, NULL);
}

void ThreadManager::remove(std::string name) {
    DeleteParam delete_param(name, memory_manager_, catalog_manager_);
    //开启用户删除线程
    pthread_create(&data_remove_thread_, NULL, &data_delete_task, &delete_param);
    pthread_join(data_remove_thread_, NULL);
}

void ThreadManager::open(std::string name) {
    //用户执行线程一共8个
}

ThreadManager::ThreadManager(DiskManager *disk_manager, CatalogManager *catalog_manager,
                             MemoryManager *memory_manager) {
    disk_manager_ = disk_manager;
    catalog_manager_ = catalog_manager;
    memory_manager_ = memory_manager;
}
