//
// Created by ctrlz on 2023/3/17.
//

#ifndef MYSERVER_STRINGUTILS_H
#define MYSERVER_STRINGUTILS_H

#include <vector>
#include <string>

namespace Utils {
    class StringUtils {
    public:
        static void Split(std::vector<std::string> &, const std::string &, const char *);

        static void Split(std::vector<std::string> &, const std::string &, const std::string &);
    };
}




#endif //MYSERVER_STRINGUTILS_H
