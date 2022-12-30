#ifndef UTILS_H
#define UTILS_H

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
std::string get_last_path(std::string path);

//获取当前系统时间
std::string get_system_time();

std::string get_user_name();

std::string type_to_string(FileType type);

#endif