//
// Created by ctrlz on 23-1-20.
//

#ifndef MYSERVER_ITABLERECORD_H
#define MYSERVER_ITABLERECORD_H

namespace DBAdapter {
#define MAX_TABLE_NAME_LEN 32
    struct ITableRecord {
        char name[MAX_TABLE_NAME_LEN];
        unsigned int id;
        typedef int Key;
    };
}

#endif //MYSERVER_ITABLERECORD_H
