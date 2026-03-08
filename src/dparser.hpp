#ifndef DPARSER_HPP
#define DPARSER_HPP
#include "dlist.hpp"
class DParser {
public:
    DParser();
    ~DParser();
    void ReadFileIn();
private:
    char* m_file_path;
    char* m_parsed_buf;

};
#endif // DLIST_HPP