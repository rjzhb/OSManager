//
// Created by 86183 on 2022/12/24.
//

#include "MemoryManager.h"

MemoryManager::MemoryManager(DiskManager *disk_manager) {
    //初始化free_page_list,大小为8
    for (int i = 0; i < 8; i++) {
        Page page;
        page.pageId = page_id++;
        page.inode = NULL;
        free_page_list_.push_back(&page);
    }
}

//分配内存
void MemoryManager::alloc(Inode *inode) {
    if (free_page_list_.empty()) {
        //启用LRU页面置换算法
        //置换出的页面写入兑换区
        Page *replace_page = alloc_page_list_.back();
        disk_manager_->swap_write(replace_page);
        alloc_page_list_.pop_back();
        //更新页表和alloc_list
        Page page;
        page.pageId = page_id;
        page.inode = inode;
        page_table_[page_id] = reinterpret_cast<void *> (&inode);
        alloc_page_list_.push_front(&page);
        page_id++;
    } else {
        Page *free_page = free_page_list_.front();
        free_page_list_.pop_front();
        free_page->inode = inode;
        alloc_page_list_.push_front(free_page);
    }

}

//释放内存
void MemoryManager::free(Inode *inode) {
    for (auto it: alloc_page_list_) {
        if (it->inode->name == inode->name) {
            alloc_page_list_.remove(it);
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




