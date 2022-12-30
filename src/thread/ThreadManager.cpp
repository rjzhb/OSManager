//
// Created by 86183 on 2022/12/24.
//

#include <iostream>
#include "ThreadManager.h"

void ThreadManager::data_create_task(std::string name, std::string data) {
    pthread_mutex_lock(&mutex_A);
    //调用目录管理功能建立目录项
    catalog_manager_->create_file(name, data);
    pthread_mutex_unlock(&mutex_A);
}

void ThreadManager::data_delete_task(std::string name) {
    pthread_mutex_lock(&mutex_A);
    if (memory_manager_->judge_memory(name)) {
        std::cout << "删除文件失败，该文件数据在内存中，需关闭后再试" << std::endl;
        return;
    }
    //调用目录管理删除文件功能删除数据
    catalog_manager_->rmfile(name);
    pthread_mutex_unlock(&mutex_A);
}


void ThreadManager::data_call_task(std::string name) {
    pthread_mutex_lock(&mutex_A);
    if (memory_manager_->judge_memory(name)) {
        std::cout << "打开文件失败，该文件正处于打开状态" << std::endl;
        return;
    }
    catalog_manager_->open(name);
    pthread_mutex_unlock(&mutex_A);
}


//下面是暴露给用户的接口

void ThreadManager::create(std::string name, std::string data) {


}

void ThreadManager::remove(std::string name) {

}
