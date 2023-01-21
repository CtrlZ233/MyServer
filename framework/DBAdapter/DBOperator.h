#ifndef DB_OPERATOR_H_

#define DB_OPERATOR_H_


#include <mysql/mysql.h>
#include "ITableRecord.h"
#include "TableCache.h"

namespace DBAdapter {
    static MYSQL mysql;
    static const char *host = "127.0.0.1";
    static const char *user = "root";
    static const char *passwd = "123456";
    static const char *db_name = "MyServerDB";

    void connect_DB();

    template <typename Table>
    class TableOperator {
        public:
            static bool AddRecord(std::shared_ptr<Table> t);

            static void DeleteRecord(typename Table::Key &key);

            static std::shared_ptr<Table> QueryRecored(typename Table::Key &key);
    };

    template<typename Table>
    std::shared_ptr<Table> TableOperator<Table>::QueryRecored(typename Table::Key &key) {
        std::shared_ptr<Table> record = TableCache<Table>::Instance().Query(key);
        if (record == nullptr) {
            // TODO: query database
        }
        return record;
    }

    template<typename Table>
    void TableOperator<Table>::DeleteRecord(typename Table::Key &key) {
        TableCache<Table>::Instance().Delete(key);
        // TODO: delete database
    }

    template<typename Table>
    bool TableOperator<Table>::AddRecord(std::shared_ptr<Table> t) {
        if (!TableCache<Table>::Instance().Add(t)) {
            return false;
        }
        // TODO: insert database

        return true;
    }

}


#endif