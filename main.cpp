#include <iostream>
#include "DiskManager.h"
#include "CatalogManager.h"




int main() {
    DiskManager *diskManager = new DiskManager();
    diskManager->print_free_blocks();
    delete diskManager;
    return 0;
}
