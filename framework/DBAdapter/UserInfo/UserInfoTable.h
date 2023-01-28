//
// Created by ctrlz on 23-1-28.
//

#ifndef MYSERVER_USERINFOTABLE_H
#define MYSERVER_USERINFOTABLE_H

#include "ITableRecord.h"
#include <string>
namespace DBAdapter {
#define MAX_USER_NAME_LEN 32
#define MAX_USER_PASSWD_LEN 16
    struct UserInfoKey;
    struct UserInfoTableRecord {
        DEFINE_TABLE_BASE_ATTR("User", 1)
        unsigned int uid;
        char name[MAX_USER_NAME_LEN];
        char passwd[MAX_USER_PASSWD_LEN];

        typedef UserInfoKey Key;
    };

    struct UserInfoKey {
        std::string name;
        static UserInfoKey From(UserInfoTableRecord record) {
            return UserInfoKey{ std::string (record.name) };
        }
    };
}


#endif //MYSERVER_USERINFOTABLE_H
