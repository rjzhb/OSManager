//
// Created by 86183 on 2022/12/30.
//

#ifndef OSMANAGER_USERMANAGER_H
#define OSMANAGER_USERMANAGER_H


#include "../kernel/catalog/CatalogManager.h"
#include "../kernel/thread/ThreadManager.h"

class UserManager {
public:


private:
    CatalogManager* catalog_manager_;
    DiskManager * disk_manager_;
    MemoryManager *memory_manager_;
    ThreadManager *thread_manager_;

};


#endif //OSMANAGER_USERMANAGER_H
