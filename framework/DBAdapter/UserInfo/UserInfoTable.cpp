//
// Created by ctrlz on 23-1-28.
//

#include "UserInfoTable.h"
#include "DBOperator.h"
#include <memory>
namespace DBAdapter {
    void RecordTest() {
        std::string u_name = "test1";
        std::string u_passwd = "12345678";
        auto record = std::make_shared<UserInfoTableRecord>(u_name, u_passwd);
        TableOperator<UserInfoTableRecord>::AddRecord(record);
    }
}