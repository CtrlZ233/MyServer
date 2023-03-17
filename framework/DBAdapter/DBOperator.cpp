//
// Created by ctrlz on 23-3-4.
//

#include <mysql/mysql.h>
#include "DBOperator.h"

static MYSQL *DB_CONNECTION;
namespace DBAdapter {
    bool ConnectDB() {
        DB_CONNECTION = new MYSQL ;
        mysql_init(DB_CONNECTION);
        if (mysql_real_connect(DB_CONNECTION, HOST, USER, PASSWD, DB_NAME, 0, NULL, CLIENT_FOUND_ROWS)) {
            printf("connect db success!\n");
            return true;
        }
        return false;
    }

    static bool connect_res = ConnectDB();

    std::string QueryRecordFromDB(const char *tableName, const char *condition) {
        std::string ans;
        std::string sql = "select * from " + std::string(tableName);
        sql += " where " + std::string(condition) + ";";
//        printf("[QueryRecordFromDB]sql: %s\n", sql.c_str());
        if(mysql_query(DB_CONNECTION, sql.c_str())) {
            printf("query db failed!");
            return ans;
        }

        MYSQL_RES *query_res = mysql_store_result(DB_CONNECTION);
        MYSQL_ROW res_row;
        if (query_res) {
            auto row = mysql_num_rows(query_res);
            auto col = mysql_num_fields(query_res);
            for (int i = 1; i < row + 1; ++i) {
                res_row = mysql_fetch_row(query_res);
                for (int j = 0; j < col; ++j) {
                    ans += res_row[j];
                    ans += ",";
                }
                ans += ";";
            }
        }
        mysql_free_result(query_res);
        return ans;
    }

    bool AddRecord2DB(const char *tableName, const char *dataStream) {
        std::string sql = "insert into " + std::string(tableName);
        sql += " values(" + std::string(dataStream) + ");";
        printf("[AddRecord2DB]sql: %s\n", sql.c_str());
        if(mysql_query(DB_CONNECTION, sql.c_str())) {
            printf("add db failed\n");
            return false;
        }
        return true;
    }

    bool DeleteRecordFromDB(const char *tableName, const char *condition) {
        std::string sql = "delete from " + std::string(tableName);
        sql += " where " + std::string(condition) + ";";
        printf("[DeleteRecordFromDB]sql: %s\n", sql.c_str());
        if(mysql_query(DB_CONNECTION, sql.c_str())) {
            printf("delete db failed\n");
            return false;
        }
        return true;
    }
}