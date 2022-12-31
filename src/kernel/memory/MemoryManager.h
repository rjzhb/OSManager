//
// Created by 86183 on 2022/12/24.
//

#ifndef OSMANAGER_MEMORYMANAGER_H
#define OSMANAGER_MEMORYMANAGER_H

#include "../disk/DiskManager.h"
#include <unordered_map>
#include <list>

class MemoryManager {
public:
    //构造函数根据自身情况添加参数
    MemoryManager(DiskManager *disk_manager);

    ~MemoryManager();

    //分配内存
    void alloc(Inode *inode);

    //释放内存
    void free(Inode *inode);

    //判断内存里是否已经打开了该文件
    bool judge_memory(std::string name);

    //显示内存信息
    void show_memory();
private:
    //页表
    std::unordered_map<int, void *> page_table_;
    //已分配内存页
    std::list<FilePage *> alloc_page_list_;
    //空闲内存页
    std::list<FilePage *> free_page_list_;
    //磁盘管理器
    DiskManager *disk_manager_;

};


#endif //OSMANAGER_MEMORYMANAGER_H
