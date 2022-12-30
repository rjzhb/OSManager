//
// Created by 86183 on 2022/12/24.
//
#include <iostream>
#include "DiskManager.h"
#include "utils.h"

DiskManager::DiskManager() {
    //初始化空闲块
    for (int i = 0; i < MAX_NUMBER_OF_GROUPS; i++) {
        int count_free = 0;

        for (int j = 1; j < MAX_FREE_BLOCK; j++) {
            free_block_list_[i][j] = 9 * i + j - 2;
            count_free++;//空闲块数
        }

        if (i != 0) {
            //不是第0组,每次都需要保存前一组的下标
            free_block_list_[i][1] = i - 1;
        } else {
            free_block_list_[i][1] = -1;
        }

        //下标0表示每组的空闲块数量
        free_block_list_[i][0] = count_free;
    }

    last_i = MAX_NUMBER_OF_GROUPS - 1;
    last_j = MAX_FREE_BLOCK - 1;


}


void DiskManager::print_free_blocks() {
    std::cout << "初始空闲块链：" << std::endl
              << "组别 " << "空闲块数 " << "上一组"
              << " 空闲块 空闲块\t...\t...\t...\t...\t...\t...\t..."
              << std::endl;

    for (int i = 0; i < last_i + 1; i++) {
        std::cout << i << ": \t";
        for (int j = 0; j < MAX_FREE_BLOCK; j++) {
            if (i == last_i && j > last_j) {
                break;
            }

            std::cout << free_block_list_[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

FilePage *DiskManager::swap_read() {
    if (swap_list_.empty()) {
        std::cout << "兑换区为空" << std::endl;
    }
    FilePage *block = swap_list_.front();
    swap_list_.pop_front();
    return block;
}

void DiskManager::swap_write(FilePage *page) {
    if (swap_list_.size() >= SWAP_BLOCK_NUMBER) {
        swap_read();
    }
    swap_list_.push_back(page);
}

void DiskManager::alloc_free_block(Dentry *dentry) {
    //加入映射
    if (dentry_map_.find(path) == dentry_map_.end()) {
        //如果map里面没有dentry链表,则创建dentry链表
        std::list<Dentry *> dentry_list;
        dentry_list.push_back(dentry);
        dentry_map_[path] = dentry_list;
    } else {
        //先判断磁盘块是否已经有了此项
        auto list = dentry_map_[path];
        for (auto it: list) {
            if (it->name == dentry->name && it->type == dentry->type) {
                std::cout << "分配磁盘块失败，该文件已存在" << std::endl;
                return;
            }
        }
        dentry_map_[path].push_back(dentry);
    }

    //更新上一级映射
    if (path != "/") {
        std::string the_last_path = get_last_path(path);
        for (auto it: dentry_map_[the_last_path]) {
            if (it->type == FileType::FOLDER) {
                it->children.push_back(dentry);
            }
        }
    }

    //计算需要分配的大小
    int alloc_size = 0;
    //每块空闲块的大小
    const int block_size = DISK_SIZE / DISK_BLOCK_NUMBER;
    switch (dentry->type) {
        case FileType::FILE :
            alloc_size = dentry->inode->data.size();
            break;
        case FileType::FOLDER:
            return;
    }

    //需要分配的空闲块个数
    int block_count = alloc_size / block_size;
    int block_groups = (block_count + MAX_FREE_BLOCK - last_j) / MAX_NUMBER_OF_BLOCKS;
    int block_per_count = (block_count + MAX_FREE_BLOCK - last_j) % MAX_NUMBER_OF_BLOCKS;
    //分配空闲块
    last_i -= block_groups;
    last_j -= block_per_count;

    if (last_i < 0) {
        std::cout << "error: 分配空闲块失败，原因：空闲块不足" << std::endl;
    }

    free_block_list_[last_i][0] = MAX_FREE_BLOCK - block_per_count;
    for (int i = last_i + 1; i < MAX_NUMBER_OF_GROUPS; i++) {
        free_block_list_[i][0] = 0;
    }

}

void DiskManager::delete_free_block(Dentry *dentry) {
    if (dentry_map_.find(path) == dentry_map_.end()) {
        std::cout << "文件不存在" << std::endl;
        return;
    }

    bool flag = false;
    //删除链表中的dentry
    for (auto it: dentry_map_[path]) {
        if (it->name == dentry->name && it->type == dentry->type) {
            dentry_map_[path].remove(it);
            flag = true;
            break;
        }
    }

    if (!flag) {
        std::cout << "文件不存在" << std::endl;
        return;
    }

    //更新上一级映射
    if (path != "/" && dentry->type == FileType::FOLDER) {
        std::string the_last_path = get_last_path(path);
        for (auto it: dentry_map_[the_last_path]) {
            if (it->type == FileType::FOLDER) {
                for (auto it = dentry_map_[the_last_path].begin(); it != dentry_map_[the_last_path].end(); it++) {
                    if ((*it)->name == dentry->name && (*it)->type == dentry->type) {
                        dentry_map_[the_last_path].erase(it);
                    }
                }
            }
        }
    }

    //计算需要释放的大小
    int alloc_size = 0;
    //每块空闲块的大小
    const int block_size = DISK_SIZE / DISK_BLOCK_NUMBER;
    switch (dentry->type) {
        case FileType::FILE :
            alloc_size = dentry->inode->data.size();
            break;
        case FileType::FOLDER:
            alloc_size = 0;
            return;
    }
    //需要释放的空闲块个数
    int block_count = alloc_size / block_size;
    int block_groups = (block_count + last_j - 2) / MAX_NUMBER_OF_BLOCKS - 1;
    int block_per_count = (block_count + last_j - 2) % MAX_NUMBER_OF_BLOCKS;
    //释放空闲块
    last_i += block_groups;
    last_j += block_per_count;

    free_block_list_[last_i][0] = MAX_FREE_BLOCK + block_per_count;
    for (int i = last_i - 1; i >= 0; i--) {
        free_block_list_[i][0] = MAX_NUMBER_OF_BLOCKS;
    }

}

auto DiskManager::get_dentry_list(std::string path) -> std::list<Dentry *> {
    if (dentry_map_.find(path) == dentry_map_.end()) {
        return {};
    }
    return dentry_map_[path];
}


