#include <string>
#include "define.h"

#ifdef linux

#include <unistd.h>
#include <pwd.h>

#endif

#ifdef _WIN32
#include<Windows.h>
#endif

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
