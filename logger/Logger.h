/*
* @Author: Qianhua Liu
* @Date: 2024-03-02
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_LOGGER_LOGGER_H
#define LOCALMINMAX_LOGGER_LOGGER_H

#include "common/Math.h"

namespace localminmax::logger {
constexpr char MEASUREMENT_MODULE[] = "MEASUREMENT";
constexpr char DEFECTRESOLVER_MODULE[] = "DEFECTRESOLVER";
constexpr char CONTROLLER_MODULE[] = "CONTROLLER";
constexpr char MYSQL_MODULE[] = "MYSQL";
constexpr char PARSER_MODULE[] = "PARSER";
constexpr char INFO[] = "INFO";
constexpr char WARNING[] = "WARNING";
constexpr char ERROR[] = "ERROR";
constexpr char LOGGING_FILE[] = "localminmax.log";

constexpr int BUFFER_MAX_LEN = 4096;

void logInfo(const char* module, const char* fmt, ...)__attribute__((format(printf, 2, 3)));
void logError(const char* module, const char* fmt, ...)__attribute__((format(printf, 2, 3)));
void logWarning(const char* module, const char* fmt, ...)__attribute__((format(printf, 2, 3)));

} // localminmax::logger

#endif // LOCALMINMAX_LOGGER_LOGGER_H