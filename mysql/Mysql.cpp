/*
* @Author: Qianhua Liu
* @Date: 2024-03-02
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/

#include "mysql/Mysql.h"

#include <iostream>

namespace localminmax::mysql {
Mysql::Mysql() 
{
    mysql_init(&m_mysql);
}

Mysql::~Mysql()
{
    mysql_close(&m_mysql);
}

bool Mysql::connectDatabase(const std::string& database, const std::string& host, 
                            const std::string& user, const std::string& passward, 
                            const int64_t port, std::string& error_msg)
{
    if (!mysql_real_connect(&m_mysql, host.c_str(), user.c_str(), 
                            passward.c_str(), database.c_str(), port, NULL, 0)) {
        error_msg = mysql_error(&m_mysql);
        return false;
    }
    return true;
}

bool Mysql::queryDatabase(const std::string& query_sql, std::vector<std::vector<std::string>>& result,
                          std::string& error_msg)
{
    if (mysql_real_query(&m_mysql, query_sql.c_str(), query_sql.size())) {
        error_msg = mysql_error(&m_mysql);
        return false;
    }
    MYSQL_RES* query_result = mysql_store_result(&m_mysql);
    if (query_result == nullptr) {
        error_msg = mysql_error(&m_mysql);
        return false;
    }
    int64_t fields_num = mysql_num_fields(query_result);
    MYSQL_ROW row;
    while (row = mysql_fetch_row(query_result)) {
        std::vector<std::string> cur_row_result = {};
        for (int64_t id = 0; id < fields_num; ++id, ++row) {
            cur_row_result.emplace_back(std::string(*row));
        }
        result.emplace_back(std::move(cur_row_result));
    }
    mysql_free_result(query_result);
    return true;
}

} // localminmax::mysql
