//
// Created by 86183 on 2022/12/24.
//

#include "MemoryManager.h"

//分配内存块：为执行线程获得的文件数据分配内存块，每个线程默认分配8块。
void MemoryManager::alloc(Inode *inode) {

}

//回收内存：执行线程结束后回收其文件数据所占用的内存。
void MemoryManager::free(Inode *inode) {

}


void initNode(struct nodespace* p) {
    if (p == NULL) { //如果为空则新创建一个
        p = (struct nodespace*)malloc(sizeof(struct nodespace));
    }
    p->teskid = -1;
    p->begin = 0;
    p->size = 2560;
    p->status = 1;
    p->next = NULL;
}
