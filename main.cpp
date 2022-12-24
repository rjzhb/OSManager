#include <iostream>
#include "DiskManager.h"

int main() {
    DiskManager * diskManager = new DiskManager();
    diskManager->print_free_blocks();
    return 0;
}
