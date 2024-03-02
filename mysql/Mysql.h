/*
* @Author: Qianhua Liu
* @Date: 2024-03-02
* @Description: 
* @Note: Copyright (c) 2024, Qianhua Liu Inc., All rights reserved
*/
#ifndef LOCALMINMAX_MYSQL_MYSQL_H
#define LOCALMINMAX_MYSQL_MYSQL_H

#include <mysql/mysql.h>
#include <string>
#include <vector>

namespace localminmax::mysql {
constexpr char DEFAULT_HOST[] = "localhost";
constexpr char DEFAULT_USER[] = "root";
constexpr char DEFAULT_PASSWARD[] = "2020151016";
constexpr char DEFAULT_DATABASE[] = "localminmax";
constexpr int64_t DEFAULT_PORT = 3306;

class Mysql {
public:
    using MysqlResult = std::vector<std::vector<std::string>>;
    Mysql();
    ~Mysql();

    bool connectDatabase(const std::string& database, const std::string& host, 
                         const std::string& user, const std::string& passward, 
                         const int64_t port, std::string& error_msg);
    bool queryDatabase(const std::string& query_sql, std::vector<std::vector<std::string>>& result, 
                       std::string& error_msg);

private:
    MYSQL m_mysql;
};

} // localminmax::mysql

#endif // LOCALMINMAX_MYSQL_MYSQL_H