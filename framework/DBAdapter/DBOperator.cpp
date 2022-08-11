#include "DBOperator.h"

namespace Utils {
    const char *DBAdapter::host = "127.0.0.1";
    const char *DBAdapter::user = "root";
    const char *DBAdapter::passwd = "123456";
    const char *DBAdapter::db_name = "ServerDB";

    DBAdapter::DBAdapter() {
        mysql_init(&mysql);
        mysql_real_connect(&mysql, host, user, passwd, db_name, 0, NULL, 0);
    }

    DBAdapter::~DBAdapter() {
        mysql_close(&mysql);
    }
}