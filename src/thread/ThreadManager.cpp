//
// Created by 86183 on 2022/12/24.
//

#include "ThreadManager.h"

void ThreadManager::data_create_task(std::string name, std::string path, std::string data) {
    //申请向磁盘分配空闲块

    //调用目录管理功能建立目录项


}

void ThreadManager::data_delete_task(std::string name, std::string path) {
    //调用目录管理删除文件功能删除数据
    catalog_manager_->rmfile(name);
}


void ThreadManager::data_call_task(std::string name, std::string path) {
    //将文件从外存调入内存
}


void ThreadManager::create(std::string name, std::string path, std::string data) {

}

void ThreadManager::remove(std::string name, std::string path) {

}
