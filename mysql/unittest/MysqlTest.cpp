/*
* @Author: Qianhua Liu
* @Date: 2024-01-07
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#include <gtest/gtest.h>

#include "mysql/Mysql.h"

namespace localminmax::mysql::unittest {

TEST(MysqlTest, testMysql)
{
    std::unique_ptr<Mysql> mysql = std::make_unique<Mysql>();
    std::string error_msg = "";
    bool status = true;
    const std::string test_sql = "SELECT * FROM mysqltest;";

    mysql->connectDatabase(DEFAULT_DATABASE, DEFAULT_HOST, DEFAULT_USER, DEFAULT_PASSWARD, 
                           DEFAULT_PORT, error_msg);

    Mysql::MysqlResult result = {};
    status = mysql->queryDatabase(test_sql, result, error_msg);
    EXPECT_TRUE(status) << "error_msg: " << error_msg << std::endl;

    Mysql::MysqlResult golden = {
        {"0", "1.000000", "2.000000"}, 
        {"1", "1.000000", "4.000000"}, 
        {"2", "1.000000", "4.000000"}
    };
    EXPECT_EQ(golden, result);
}

} // localminmax::mysql::unittest