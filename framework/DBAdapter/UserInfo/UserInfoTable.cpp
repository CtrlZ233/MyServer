//
// Created by ctrlz on 2023/3/17.
//
#include "UserInfoTable.h"
#include "StringUtils.h"

namespace DBAdapter {
    using std::vector;
    using std::string;
    UserInfoTableRecord::UserInfoTableRecord(string &u_name, string &u_passwd) {
        if (u_name.length() > MAX_USER_NAME_LEN || u_passwd.length() > MAX_USER_PASSWD_LEN) {
            throw std::runtime_error("invalid user data");
        }
        name = std::move(u_name);
        passwd = std::move(u_passwd);
    }

    void UserInfoTableRecord::FromStr(vector<UserInfoTableRecord> &records, const string &data_stream) {
        vector<string> records_str;
        Utils::StringUtils::Split(records_str, data_stream, ";");
        for (auto const &str : records_str) {
            vector<string> split_record;
            Utils::StringUtils::Split(split_record, str, ",");
            if (split_record.size() > MAX_ELEM_NUM) {
                printf("decode db record error");
                return;
            }
            records.emplace_back(split_record[0], split_record[1]);
        }
    }
}