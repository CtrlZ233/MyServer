#ifndef DB_OPERATOR_H_

#define DB_OPERATOR_H_


#include <mysql/mysql.h>
#include "ITableRecord.h"
#include "TableCache.h"

namespace DBAdapter {
    static MYSQL mysql;
    static const char *HOST = "127.0.0.1";
    static const char *USER = "root";
    static const char *PASSWD = "123456";
    static const char *DB_NAME = "MyServerDB";

    bool ConnectDB();

    bool AddRecord2DB(const char *tableName, const char *dataStream);

    bool DeleteRecordFromDB(const char *tableName, const char *condition);

    std::string QueryRecordFromDB(const char *tableName, const char *condition);

    template <typename Table>
    class TableOperator {
        public:
            static bool AddRecord(std::shared_ptr<Table> t);

            static bool DeleteRecord(const typename Table::Key &key);

            static std::shared_ptr<Table> QueryRecord(const typename Table::Key &key);
    };

    template<typename Table>
    std::shared_ptr<Table> TableOperator<Table>::QueryRecord(const typename Table::Key &key) {
        std::shared_ptr<Table> record = TableCache<Table>::Instance().Query(key);
        if (record == nullptr) {
            // TODO: query database & insert to cache
            const char *tableName = Table::tableName;
            std::string keyCondition = key.Condition();
            auto str_record = QueryRecordFromDB(tableName, keyCondition.c_str());
        }
        return record;
    }

    template<typename Table>
    bool TableOperator<Table>::DeleteRecord(const typename Table::Key &key) {
        TableCache<Table>::Instance().Delete(key);
        // TODO: delete database
        const char *tableName = Table::tableName;
        std::string keyCondition = key.Condition();
        return DeleteRecordFromDB(tableName, keyCondition.c_str());
    }

    template<typename Table>
    bool TableOperator<Table>::AddRecord(std::shared_ptr<Table> t) {
        if (!TableCache<Table>::Instance().Add(t)) {
            return false;
        }
        // TODO: insert database
        const char *tableName = Table::tableName;
        std::string dataStream = t->ToStream();
        return AddRecord2DB(tableName, dataStream.c_str());
    }

}


#endif