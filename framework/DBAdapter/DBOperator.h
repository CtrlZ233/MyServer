#ifndef DB_OPERATOR_H_

#define DB_OPERATOR_H_


#include <mysql/mysql.h>

namespace Utils {

    class DBAdapter {
    public:
        DBAdapter();

        virtual void AddRecord() = 0;

        virtual void DeleteRecord() = 0;;

        virtual bool QueryRecored() = 0;

        virtual ~DBAdapter();

    private:
        MYSQL mysql;
        static const char *host;
        static const char *user;
        static const char *passwd;
        static const char *db_name;
        
    };

}


#endif