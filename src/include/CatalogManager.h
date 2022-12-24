//
// Created by 86183 on 2022/12/24.
//

#ifndef OSMANAGER_CATALOGMANAGER_H
#define OSMANAGER_CATALOGMANAGER_H


#include "DiskManager.h"

class CatalogManager {
public:
    //构造函数根据自身情况添加参数
    CatalogManager(DiskManager *disk_manager);

    ~CatalogManager() = default;


    //新建目录
    void mkdir(std::string dir_name);

    //删除目录
    void rmdir(std::string dir_name);

    //为文件建立目录项
    void create_dentry(Inode inode);

    //删除文件
    void rmfile(std::string file_name);

private:
    //用上的数据结构都放这
};


#endif //OSMANAGER_CATALOGMANAGER_H
