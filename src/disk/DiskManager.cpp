//
// Created by 86183 on 2022/12/24.
//
#include <iostream>
#include "DiskManager.h"

DiskManager::DiskManager() {
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

void DiskManager::Swapping_read(){
    int i;
    for(i=0;i<100;i++)
    {
        swaping_ara[i]=ready_to_read[i];
    }
}
void DiskManager::Swapping_write(){
    int i;
    for(i=0;i<100;i++)
    {
        ready_to_write[i]=swaping_ara[i];
    }
}