//
// Created by ctrlz on 2023/3/17.
//

#include "StringUtils.h"

namespace Utils {
    using std::vector;
    using std::string;

    void StringUtils::Split(vector<string> &tokens, const string &src, const string &delimiters) {
        // Skip delimiters at beginning.
        string::size_type lastPos = src.find_first_not_of(delimiters, 0);
        // Find first "non-delimiter".
        string::size_type pos = src.find_first_of(delimiters, lastPos);
        while (string::npos != pos || string::npos != lastPos)
        {
            // Found a token, add it to the vector.
            tokens.push_back(src.substr(lastPos, pos - lastPos));
            // Skip delimiters.  Note the "not_of"
            lastPos = src.find_first_not_of(delimiters, pos);
            // Find next "non-delimiter"
            pos = src.find_first_of(delimiters, lastPos);
        }
    }

    void StringUtils::Split(vector<string> &tokens, const string &src,const char *delimiters) {
        Split(tokens, src, string(delimiters));
    }
}