//
// Created by 86183 on 2022/12/24.
//

#ifndef OSMANAGER_DISKMANAGER_H
#define OSMANAGER_DISKMANAGER_H

#include <cstddef>
#include <list>
#include <unordered_map>
#include "utils.h"
#include <queue>

class DiskManager {
public:

    DiskManager();

    ~DiskManager() = default;

    //分配空闲块
    void alloc_free_block(Dentry *dentry);

    //释放空闲块
    void delete_free_block(Dentry *dentry);

    //输出所有空闲块
    void print_free_blocks();

    //兑换区读写
    Page *swap_read();

    void swap_write(Page *page);

    //通过path获得磁盘链
    auto get_dentry_list(std::string path) -> std::list<Dentry *>;

    //显示磁盘信息
    void show_disk();

private:

    //数据组织映射
    std::unordered_map<std::string, std::list<Dentry *>> dentry_map_;
    //空闲块(成组链接法)
    int free_block_list_[MAX_NUMBER_OF_GROUPS][MAX_FREE_BLOCK];
    //指向最后一个空闲块的指针
    int last_i = 0;
    int last_j = 0;

    //兑换区
    std::list<Page *> swap_list_;
};


#endif //OSMANAGER_DISKMANAGER_H
