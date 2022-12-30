//
// Created by 86183 on 2022/12/24.
//

#ifndef OSMANAGER_MEMORYMANAGER_H
#define OSMANAGER_MEMORYMANAGER_H


#include "define.h"
#include "DiskManager.h"
#include <unordered_map>
#include <list>

class MemoryManager {
public:
    //构造函数根据自身情况添加参数
    MemoryManager(DiskManager *disk_manager);

    ~MemoryManager();

    void alloc(Inode *inode);

    void free(Inode *inode);

    bool judge_memory(std::string name);
private:
    //页表
    std::unordered_map<int, void *> page_table_;
    //已分配内存页
    std::list<Page*> alloc_page_list_;
    //空闲内存页
    std::list<FilePage*> free_page_list_;

    DiskManager *disk_manager_;

};


#endif //OSMANAGER_MEMORYMANAGER_H
