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
        return NULL;
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
    if (free_thread_list_.empty()) {
        //需要关闭最早打开的文件
        FileThread file_thread = alloc_thread_list_.front();
        //释放内存
        Inode inode;
        inode.name = file_thread.name;
        catalog_manager_->close(name);
        alloc_thread_list_.pop_front();
        free_thread_list_.push_back(file_thread.pthread);
    }
    //为任务分配线程
    pthread_t pthread = free_thread_list_.front();
    free_thread_list_.pop_front();
    using CallParam = DeleteParam;
    CallParam param(name, memory_manager_, catalog_manager_);
    pthread_create(&pthread, NULL, &data_call_task, &param);
    pthread_join(pthread, NULL);
}

ThreadManager::ThreadManager(DiskManager *disk_manager, CatalogManager *catalog_manager,
                             MemoryManager *memory_manager) {
    disk_manager_ = disk_manager;
    catalog_manager_ = catalog_manager;
    memory_manager_ = memory_manager;
}
