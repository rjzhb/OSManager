//
// Created by 86183 on 2022/12/24.
//

#ifndef OSMANAGER_DEFINE_H
#define OSMANAGER_DEFINE_H

#include <cstddef>
#include <string>
#include <vector>


#ifdef linux

#include <unistd.h>
#include <pwd.h>

#endif

#ifdef _WIN32
#include<Windows.h>
#endif

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

//当前路径
std::string path;
//计数
int inum = 0;

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
    struct nodespace *next;  // 后指针
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


//获取上一级目录字符串
std::string get_last_path(std::string path) {
    if (path == "/")return "/";
    int end = 0;
    for (int i = path.size() - 2; i >= 0; i--) {
        if (path[i] == '/') {
            end = i;
            break;
        }
    }
    return end == 0 ? "/" : path.substr(0, end);
}

//获取当前系统时间
std::string get_system_time() {
    time_t nowtime;
    tm *p;;
    time(&nowtime);
    p = localtime(&nowtime);
    std::string res =
            std::to_string(p->tm_year) + "年" + std::to_string(p->tm_mon) + "月" + std::to_string(p->tm_mday) + "日" +
            std::to_string(p->tm_hour) + "时" + std::to_string(p->tm_min) + "分" +
            std::to_string(p->tm_sec) + "秒";
    return res;
}


std::string get_user_name() {
#if defined linux   //linux system
    uid_t userid;
    struct passwd *pwd;
    userid = getuid();
    pwd = getpwuid(userid);
    return pwd->pw_name;

#elif defined _WIN32  //windows system
    const int MAX_LEN = 100;
    char szBuffer[MAX_LEN];
    DWORD len = MAX_LEN;
    if( GetUserName(szBuffer, &len) )     //用户名保存在szBuffer中,len是用户名的长度
        return szBuffer;

#else  //outher system
    return "";
#endif
}


std::string type_to_string(FileType type) {
    switch (type) {
        case FileType::FILE:
            return "文件";
        case FileType::FOLDER:
            return "文件夹";
    }
}

#endif //OSMANAGER_DEFINE_H
