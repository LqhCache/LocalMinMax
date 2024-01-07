#include <mysql/mysql.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::cout << "TEST mysql start " << std::endl;

    std::string database_name = "localminmax";
    std::string test_sql = "SELECT * FROM defects;";
    MYSQL mysql;
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "root", "2020151016", database_name.c_str(), 3306, NULL, 0)) {
        std::cout << "Failed to connect to database. Error: " << mysql_error(&mysql) << std::endl;
        return 0;
    }
    if (mysql_real_query(&mysql, test_sql.c_str(), test_sql.size())) {
        std::cout << "mysql_real_query failure" << std::endl;
        return 0;
    }
    MYSQL_RES *res = mysql_store_result(&mysql);
    if (res == nullptr) {
        std::cout << "mysql_store_result failure" << std::endl;
        return 0;
    }
    MYSQL_ROW row;
    while (row = mysql_fetch_row(res)) {
        std::cout << row[0] << " " << row[1] << " " << row[2] << std::endl;
    }
    mysql_free_result(res);
    mysql_close(&mysql);

    std::cout << "TEST mysql end " << std::endl;
    return 0;
}