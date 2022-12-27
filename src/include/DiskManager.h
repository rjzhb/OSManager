//
// Created by 86183 on 2022/12/24.
//

#ifndef OSMANAGER_DISKMANAGER_H
#define OSMANAGER_DISKMANAGER_H

#include <cstddef>
#include <list>
#include "define.h"

class DiskManager {
public:

    DiskManager();

    ~DiskManager() = default;

    //

    //输出所有空闲块
    void print_free_blocks();

    //兑换区读写
    void Swapping_read();
    void Swapping_write();
private:

    //数据组织
    std::list<DiskBlock> alloc_block_list_;
    //空闲块(成组链接法)
    int free_block_list_[MAX_NUMBER_OF_GROUPS][MAX_FREE_BLOCK];
    //指向最后一个空闲块的指针
    int last_i = 0;
    int last_j = 0;
    //兑换区
    struct data{

    };
    data ready_to_read[100];
    data ready_to_write[100];
    data swaping_ara[100];
};


#endif //OSMANAGER_DISKMANAGER_H
