/*
* @Author: Qianhua Liu
* @Date: 2024-03-02
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/

#include "logger/Logger.h"

#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>

namespace {
using namespace localminmax::logger;

void writeFile(const char* buffer, const char* file_name, 
               const std::ios::openmode& openmode) 
{
    std::fstream file;
    file.open(file_name, openmode);
    file.write(buffer, strlen(buffer));
    file.close();
}

} // namespace

namespace localminmax::logger {

void logInfo(const char* module, const char* fmt, ...)
{
    char content[BUFFER_MAX_LEN] = {0};
    char* content_ptr = content;

    // log time, log module, log info
    time_t now = time(0);
    tm* local_time = localtime(&now);
    sprintf(content, "[%d-%02d-%02d %02d:%02d:%02d][%s][%s]", 1900 + local_time->tm_year, 
            1 + local_time->tm_mon, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, 
            local_time->tm_sec, module, INFO);
    int32_t prefix_len = strlen(content);

    va_list args;
    va_start(args, fmt);

    // log message
    int64_t size = vsnprintf(content_ptr + prefix_len, BUFFER_MAX_LEN - prefix_len, fmt, args);
    writeFile(content, LOGGING_FILE, std::ios::app);
    va_end(args);
}

void logError(const char* module, const char* fmt, ...)
{
    char content[BUFFER_MAX_LEN] = {0};
    char* content_ptr = content;

    // log time, log module, log error
    time_t now = time(0);
    tm* local_time = localtime(&now);
    sprintf(content, "[%d-%02d-%02d %02d:%02d:%02d][%s][%s]", 1900 + local_time->tm_year, 
            1 + local_time->tm_mon, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, 
            local_time->tm_sec, module, ERROR);
    int32_t prefix_len = strlen(content);

    va_list args;
    va_start(args, fmt);

    // log message
    int64_t size = vsnprintf(content_ptr + prefix_len, BUFFER_MAX_LEN - prefix_len, fmt, args);
    writeFile(content, LOGGING_FILE, std::ios::app);
    va_end(args);
}

void logWarning(const char* module, const char* fmt, ...)
{
    char content[BUFFER_MAX_LEN] = {0};
    char* content_ptr = content;

    // log time, log module, log warning
    time_t now = time(0);
    tm* local_time = localtime(&now);
    sprintf(content, "[%d-%02d-%02d %02d:%02d:%02d][%s][%s]", 1900 + local_time->tm_year, 
            1 + local_time->tm_mon, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, 
            local_time->tm_sec, module, WARNING);
    int32_t prefix_len = strlen(content);

    va_list args;
    va_start(args, fmt);

    // log message
    int64_t size = vsnprintf(content_ptr + prefix_len, BUFFER_MAX_LEN - prefix_len, fmt, args);
    writeFile(content, LOGGING_FILE, std::ios::app);
    va_end(args);
}

} // localminmax::logger
