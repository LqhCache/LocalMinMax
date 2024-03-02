/*
* @Author: Qianhua Liu
* @Date: 2024-01-07
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include <gtest/gtest.h>

#include "logger/Logger.h"

namespace localminmax::logger::unittest {

TEST(LoggerTest, testLogger)
{
    logInfo(CONTROLLER_MODULE, "%s", "Test info.\n");
    logError(CONTROLLER_MODULE, "%s", "Test error.\n");
    logWarning(CONTROLLER_MODULE, "%s", "Test warning.\n");
}

} // localminmax::logger::unittest