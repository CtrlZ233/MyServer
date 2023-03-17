//
// Created by ctrlz on 23-1-28.
//

#ifndef MYSERVER_USERINFOTABLE_H
#define MYSERVER_USERINFOTABLE_H

#include "ITableRecord.h"
#include <string>
#include <stdexcept>
#include <memory>
#include <vector>
namespace DBAdapter {
#define MAX_USER_NAME_LEN 32
#define MAX_USER_PASSWD_LEN 16
#define MAX_ELEM_NUM 2
    struct UserInfoKey;
    struct UserInfoTableRecord {
        DEFINE_TABLE_BASE_ATTR("Users", 1);
        std::string name;
        std::string passwd;

        UserInfoTableRecord(std::string &u_name, std::string &u_passwd);

        std::string ToStream() {
            return "\"" + name + "\"" + ", " + "\"" + passwd + "\"";
        }

        static void FromStr(std::vector<UserInfoTableRecord> &records, const std::string &data_stream);

        typedef UserInfoKey Key;
    };

    struct UserInfoCmp;
    struct UserInfoKey {
        std::string name;
        typedef UserInfoCmp Cmp;
        static UserInfoKey From(const std::shared_ptr<UserInfoTableRecord>& record) {
            return UserInfoKey{ std::string (record->name) };
        }

        std::string Condition() const {
            std::string str = "id=";
            return str + "\"" + name + "\"";
        }
        explicit UserInfoKey(std::string u_name) {
            name = std::move(u_name);
        }

        UserInfoKey(const UserInfoKey &key) {
            name = key.name;
        }

        UserInfoKey() {
            name = "null";
        }
    };

    struct UserInfoCmp {
        bool operator ()(const UserInfoKey &a, const UserInfoKey &b) const {
            return a.name < b.name;
        }
    };
}


#endif //MYSERVER_USERINFOTABLE_H
