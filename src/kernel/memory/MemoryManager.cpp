//
// Created by 86183 on 2022/12/24.
//

#include <iostream>
#include "MemoryManager.h"


MemoryManager::MemoryManager(DiskManager *disk_manager) {
    disk_manager_ = disk_manager;
    //初始化free_page_list,大小为8
    for (int i = 0; i < 8; i++) {
        FilePage page;
        free_page_list_.push_back(&page);
    }
}

//分配内存
void MemoryManager::alloc(Inode *inode) {
    if (free_page_list_.empty()) {
        //启用LRU页面置换算法
        //置换出的页面写入兑换区
        FilePage *replace_page = alloc_page_list_.back();
        for (auto it: replace_page->pageList) {
            disk_manager_->swap_write(it);
        }
        alloc_page_list_.pop_back();
        //更新页表和alloc_list
        page_table_[page_id] = reinterpret_cast<void *> (&inode);
        FilePage *page = new FilePage(inode);
        alloc_page_list_.push_front(page);
        page_id++;
    } else {
        free_page_list_.pop_front();
        FilePage *page = new FilePage(inode);
        page_table_[page_id] = reinterpret_cast<void *> (&inode);
        alloc_page_list_.push_front(page);
    }

}

//释放内存
void MemoryManager::free(Inode *inode) {
    for (auto it: alloc_page_list_) {
        if (it->inode->name == inode->name) {
            alloc_page_list_.remove(it);
            free_page_list_.push_back(it);
        }
    }
}

MemoryManager::~MemoryManager() {
    delete disk_manager_;
}


//判断是否打开了某文件
bool MemoryManager::judge_memory(std::string name) {
    for (auto it: alloc_page_list_) {
        if (it->inode->name == name) {
            return true;
        }
    }
    return false;
}

void MemoryManager::show_memory() {
    std::cout << "文件\t\t页面1\t\t\t页面2\t\t\t页面3\t\t\t页面4\t\t\t页面5\t\t\t页面6\t\t\t页面7\t\t\t页面8\t\t\t"
              << std::endl;
    for (auto it: alloc_page_list_) {
        std::cout << it->inode->name << "\t";
        for (auto item: it->pageList) {
            std::cout << reinterpret_cast<void *>(item->inode) << "\t";
        }
        std::cout << std::endl;
    }
}




