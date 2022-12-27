//
// Created by 86183 on 2022/12/24.
//

#ifndef OSMANAGER_DEFINE_H
#define OSMANAGER_DEFINE_H

#include <cstddef>
#include <string>
#include <vector>

//磁盘大小
constexpr int DISK_SIZE = 4 * 1024;
//磁盘划分块数
constexpr int DISK_BLOCK_NUMBER = 1024;
//磁盘用于文件区块数
constexpr int DIR_BLOCK_NUMBER = 900;
//磁盘用于兑换区块数
constexpr int SWAP_BLOCK_NUMBER = 124;
//每组最大10个空闲块，第0块存放本组空闲块数量，第一块指向前一组
constexpr int MAX_FREE_BLOCK = 11;
//一共多少组空闲块
constexpr int MAX_NUMBER_OF_GROUPS = 10;


enum class FileType {
    FOLDER,
    FILE,
};

//文件索引节点
struct Inode {
    //编号
    int Inum;
    //文件大小
    size_t size;
    //数据
    std::string data;
};

struct nodespace {
    int teskid;   // 任务号
    int begin;    // 开始地址
    int size;     // 大小
    int status;   // 状态 0代表占用，1代表空闲
    struct nodespace* next;  // 后指针
};


//文件目录项(树形结构)
struct Dentry {
    //文件名
    std::string fileName;
    //文件所有者
    std::string userName;
    //文件创建时间
    std::string createTime;
    //文件类型
    FileType type;
    //索引节点指针
    Inode *inode;
    //上一级目录
    Dentry *parent;
    //下一级目录
    std::vector<Dentry *> children;
};


//磁盘块结构定义
struct DiskBlock {
    int id;
    size_t size;

    DiskBlock(int id) {
        this->id = id;
        this->size = DISK_SIZE / DISK_BLOCK_NUMBER;
    }
};

//数据块，连续存储方式
struct DataBlock {
    int begin_id;
    int end_id;
    size_t size;

    //文件索引
    Inode *inode;

    DataBlock(int begin_id, int end_id) {
        this->begin_id = begin_id;
        this->end_id = end_id;
        this->size = (end_id - begin_id + 1) * (DISK_SIZE / DISK_BLOCK_NUMBER);
    }
};

#endif //OSMANAGER_DEFINE_H
