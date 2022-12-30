//
// Created by 86183 on 2022/12/24.
//

#ifndef OSMANAGER_CATALOGMANAGER_H
#define OSMANAGER_CATALOGMANAGER_H


#include "../disk/DiskManager.h"
#include "../memory/MemoryManager.h"

class CatalogManager {
public:
    //构造函数根据自身情况添加参数
    CatalogManager(DiskManager *disk_manager);

    ~CatalogManager() = default;


    //新建空目录
    void mkdir(std::string dir_name);

    //删除空目录
    void rmdir(std::string dir_name);

    //创建文件
    void create_file(std::string file_name, std::string data);

    //删除文件
    void rmfile(std::string file_name);

    //列出当前目录所有文件夹和文件
    void ls();

    //打开文件夹
    void cd(std::string dir_name);

    //打开文件
    void open(std::string file_name);

    //关闭文件
    void close(std::string file_name);

private:
    DiskManager *disk_manager_;
    MemoryManager *memory_manager_;
};


#endif //OSMANAGER_CATALOGMANAGER_H
