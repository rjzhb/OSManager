#ifndef DEFINE_H
#define DEFINE_H

#include <cstddef>
#include <string>
#include <vector>
#include <list>

//磁盘大小
constexpr int DISK_SIZE = 40 * 1024;
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
//每组用户可分配的最大空闲块数量
constexpr int MAX_NUMBER_OF_BLOCKS = 9;
//内存空间
constexpr int TOTAL_MEMORY_SIZE = 2560;
//划分内存块数
constexpr int MEMORY_BLOCK_SIZE = 64;
//每块内存大小
constexpr int PER_MEMORY_SIZE = TOTAL_MEMORY_SIZE / MEMORY_BLOCK_SIZE;

//当前路径
extern std::string path;
//计数
extern int inum;
extern int page_id;

enum class FileType {
    FOLDER,
    FILE,
};

//文件索引节点
struct Inode {
    //编号
    int Inum;
    //文件名
    std::string name;
    //文件大小
    size_t size;
    //数据
    std::string data;

};


//文件目录项(树形结构)
struct Dentry {
    //名称
    std::string name;
    //文件创建时间
    std::string createTime;
    //文件类型
    FileType type;
    //索引节点指针
    Inode *inode;
    //文件所有者
    std::string owner;
    //下一级目录
    std::vector<Dentry *> children;
};


//页(内存块)
struct Page {
    int pageId;
    //文件索引
    Inode *inode;
};

//某个文件占用的内存块
struct FilePage {
    //文件索引
    Inode *inode;
    //空闲块个数
    int freeCount;
    //文件已经分配块
    std::list<Page *> pageList;

    FilePage() {
        freeCount = 8;
    }

    FilePage(Inode *inode) {
        freeCount = 8;
        int block_count = inode->data.size() % PER_MEMORY_SIZE == 0 ? inode->data.size() / PER_MEMORY_SIZE :
                          inode->data.size() / PER_MEMORY_SIZE + 1;
        //分解字符串
        std::string data = inode->data;
        int pos = 0;
        for (int i = 0; i < 8; i++) {
            Page page;
            page.pageId = page_id++;
            Inode inode;
            inode.data = data.substr(pos, PER_MEMORY_SIZE);
            pos += PER_MEMORY_SIZE;
            page.inode = &inode;
            pageList.push_back(&page);
        }
        if (block_count > 8) {
            //启用LRU算法
            Page *page = pageList.front();
            //替换最少使用的部分字符串
            page->inode->data = data.substr(pos, inode->data.size() % PER_MEMORY_SIZE);
        }
    }
};


struct FileThread {
    std::string name;
    pthread_t pthread;

    FileThread(std::string name, pthread_t pthread) {
        this->name = name;
        this->pthread = pthread;
    }
};

#endif


