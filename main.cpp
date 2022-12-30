#include <iostream>
#include "src/kernel/disk/DiskManager.h"
#include "src/kernel/catalog/CatalogManager.h"




int main() {
    DiskManager *diskManager = new DiskManager();
    diskManager->print_free_blocks();
    delete diskManager;
    return 0;
}
