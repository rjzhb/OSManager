//
// Created by 86183 on 2022/12/24.
//

#ifndef OSMANAGER_MEMORYMANAGER_H
#define OSMANAGER_MEMORYMANAGER_H


#include "define.h"

class MemoryManager {
public:
    //构造函数根据自身情况添加参数
    MemoryManager();

    ~MemoryManager() = default;

    void alloc(Inode* inode);

    void free(Inode* inode);


private:
};


#endif //OSMANAGER_MEMORYMANAGER_H
