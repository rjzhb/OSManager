//
// Created by 86183 on 2022/12/24.
//

#include <iostream>
#include "CatalogManager.h"


void CatalogManager::mkdir(std::string dir_name) {
    Dentry dentry;
    dentry.type = FileType::FOLDER;
    dentry.name = dir_name;
    dentry.createTime = get_system_time();
    dentry.owner = get_user_name();
    disk_manager_->alloc_free_block(&dentry);
}

void CatalogManager::rmdir(std::string dir_name) {
    Dentry dentry;
    dentry.type = FileType::FOLDER;
    dentry.name = dir_name;
    disk_manager_->delete_free_block(&dentry);
}

void CatalogManager::create_file(std::string file_name, std::string data) {
    Dentry dentry;
    dentry.type = FileType::FILE;
    dentry.name = file_name;
    dentry.createTime = get_system_time();
    dentry.owner = get_user_name();
    Inode inode;
    inode.data = data;
    inode.size = data.size();
    inode.Inum = inum++;
    dentry.inode = &inode;
    disk_manager_->alloc_free_block(&dentry);
}

void CatalogManager::rmfile(std::string file_name) {
    Dentry dentry;
    dentry.type = FileType::FOLDER;
    dentry.name = file_name;
    disk_manager_->delete_free_block(&dentry);
}

void CatalogManager::ls() {
    std::list<Dentry *> list = disk_manager_->get_dentry_list(path);
    for (auto it: list) {
        std::cout << it->name << "\t\t" << type_to_string(it->type) << "\t\t" << it->owner << "\t\t" << it->createTime
                  << std::endl;
    }
}

void CatalogManager::cd(std::string dir_name) {
    path = path + "/" + dir_name + "/";
}

void CatalogManager::open(std::string file_name) {
    //从磁盘中找到该文件的数据读入内存
    auto list = disk_manager_->get_dentry_list(path);
    Inode *inode;
    bool flag = false;
    for(auto it:list){
        if(it->type == FileType::FILE && it->name == file_name){
           inode = it->inode;
           flag = true;
           break;
        }
    }

    if(!flag){
        std::cout <<"该文件不存在" <<std::endl;
    }

    //读入内存
    memory_manager_->alloc(inode);
    std::cout << inode->data << std::endl;
}

void CatalogManager::close(std::string file_name) {

}
