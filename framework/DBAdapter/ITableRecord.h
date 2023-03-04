//
// Created by ctrlz on 23-1-20.
//

#ifndef MYSERVER_ITABLERECORD_H
#define MYSERVER_ITABLERECORD_H
namespace DBAdapter {
#define MAX_TABLE_NAME_LEN 32

#define DEFINE_TABLE_BASE_ATTR(name, id)  \
    constexpr const static char tableName[MAX_TABLE_NAME_LEN] = name; \
    const static unsigned int tid = id;       \

}

#endif //MYSERVER_ITABLERECORD_H
