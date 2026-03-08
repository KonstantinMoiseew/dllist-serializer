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
    bool Serialize();
    void Info();
    void PrintDlist();

    void Set_file_in_path(const std::string& filename);
    void Set_file_out_path(const std::string& filename);
    

private:
    char* m_file_path;
    char* m_parsed_buf;
    void m_read_fileIn();
    std::vector<char*> m_string_line;
    std::vector<InfoDList> m_info_list;
    std::string m_file_in_full_path;
    std::string m_file_out_full_path;

    void m_split();
    DList* m_dlist;
};
#endif // DLIST_HPP