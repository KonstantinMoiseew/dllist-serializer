#ifndef DPARSER_HPP
#define DPARSER_HPP
#include "dlist.hpp"
#include <vector>

struct InfoDList{
    std::string msg;
    int file_line_number;
    int rand_idx;
};

class DParser {
public:
    DParser(DList* dlist = new DList());
    ~DParser();
    void Parse();
    void Info();
    

private:
    char* m_file_path;
    char* m_parsed_buf;
    void m_read_fileIn();
    void m_split();
    DList* m_dlist;
    std::vector<char*> m_string_line;
    std::vector<InfoDList> m_info_list;
};
#endif // DLIST_HPP