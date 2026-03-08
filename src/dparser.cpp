#include "dparser.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>



DParser::DParser(DList* dlist): m_dlist(dlist) {
        std::error_code ec;
        std::filesystem::path canonical_path_in = std::filesystem::canonical("./res/inlet.in", ec);
        if (ec) {
            std::cerr << "Canonical failed: " << ec.message() << std::endl;
            m_file_in_full_path = "../res/inlet.in";  // Fallback
        } else {
            m_file_in_full_path = canonical_path_in.string();
        }

        std::filesystem::path canonical_path_out = std::filesystem::canonical("./res/outlet.out", ec);
        if (ec) {
            std::cerr << "Canonical failed: " << ec.message() << std::endl;
            m_file_out_full_path = "../res/outlet.out";  // Fallback
        } else {
         m_file_out_full_path = canonical_path_out.string();
        }
    
        std::cout << "Working dir: " << std::filesystem::current_path() << std::endl; //working dir (pwd) inherits from parent process.

}
DParser::~DParser(){}
void DParser::m_read_fileIn(){
    int fd = open(m_file_in_full_path.c_str(), O_RDONLY);
    if(fd == -1){
        std::cout << "Failed to open file: " << "./res/inlet.in, fd= " <<  fd << std::endl;
        return;
    }
    char** bufs;
    m_parsed_buf = new char[1000000];
    char buf[10] = {0};
    int pos = 0;
    size_t rd; 
    while((rd = read(fd, buf, 10)) > 0)
    {
        memcpy(m_parsed_buf + pos, buf, rd);
        pos = pos + rd;
    }

    m_parsed_buf[pos +1] = '\0'; //m_parsed_buf[pos] = '\n'; LF symbol 0A
    //std::cout << "m_parsed_buf: " << m_parsed_buf << std::endl;

}

void DParser::m_split(){

    m_read_fileIn();
    if (m_parsed_buf == nullptr) return;

    char* ptr = m_parsed_buf;
    
    while (*ptr) {  // Пока не конец строки
        char* line_start = ptr;     // Начало строки
        
        // Найти конец строки ('\n')
        while (*ptr && *ptr != '\n') {
            ptr++;
        }
        
        // Скопировать строку (до '\n')
        if (ptr > line_start) {
            size_t len = ptr - line_start;
            char* line = new char[len + 1];
            memcpy(line, line_start, len);
            line[len] = '\0';
            m_string_line.push_back(line);
        }
        
        // Пропустить '\n'
        if (*ptr == '\n') ptr++;
    }
    
}

void DParser::Parse(){
    m_split();

    std::cout << "Splitting: " << std::endl;
    int line_counter = 1;
    
    for (auto t : m_string_line) {
        char* tmp_ptr = t;
        char* data_start = t;      // Start of data (before ';')
        char* index_start = nullptr; // Start of index (after ';')
        int semicolon_counter = 0;
        InfoDList inf_list;
        inf_list.file_line_number = line_counter;
        
        // Find first ';'
        while (*tmp_ptr != '\0') {
            if (*tmp_ptr == ';') {
                semicolon_counter++;
                if (semicolon_counter == 1) {
                    index_start = tmp_ptr + 1;  // Point to index after ';'
                }
                break;  // Stop at first ';'
            }
            tmp_ptr++;
        }
        
        // Validate format
        if (semicolon_counter != 1 || index_start == nullptr || *index_start == '\0') {
            inf_list.msg = "Ошибка в строке " + std::to_string(line_counter) + 
                          " (need data;index format)";
            m_info_list.push_back(inf_list);
            line_counter++;
            continue;
        }
        
        // Extract DATA (before ';')
        size_t data_len = index_start - data_start;
        char* data = new char[data_len + 1];
        memcpy(data, data_start, data_len);
        data[data_len] = '\0';
        
        // Extract INDEX (after ';')
        char* index_end = index_start;
        while (*index_end != '\0' && *index_end != '\n') {
            index_end++;
        }
        size_t index_len = index_end - index_start;
        char* index_str = new char[index_len + 1];
        memcpy(index_str, index_start, index_len);
        index_str[index_len] = '\0';
        
        // Remove spaces from index
        char* clean_index = index_str;
        char* write_ptr = index_str;



        char clean_buf[32] = {0};  // Fixed size for index
        write_ptr = clean_buf;
        clean_index = index_str;
        while (*clean_index) {
            if (!isspace((unsigned char)*clean_index)) {
                *write_ptr++ = *clean_index;
            }
            clean_index++;
        }
        *write_ptr = '\0';
        
        // Parse index to int
        int rand_idx = -1;
        try {
            rand_idx = std::stoi(clean_buf);
            if (rand_idx < -1 || rand_idx >= 1000000) {
                throw std::invalid_argument("out of range");
            }
        } catch (...) {
            inf_list.msg = "Ошибка в строке " + std::to_string(line_counter) + " (invalid index: '" + std::string(index_str) + "')";
            m_info_list.push_back(inf_list);
            delete[] data;
            delete[] index_str;
            line_counter++;
            continue;
        }
        
        // SUCCESS: Add to list
        m_dlist->m_append(data);
        inf_list.rand_idx = rand_idx;
        inf_list.msg = "";
        m_info_list.push_back(inf_list);
        
        line_counter++;
        delete[] index_str;  // data managed by m_dlist
    }
    
    // Set random pointers
    std::vector<int> rand_nodes;
    for (auto& info : m_info_list) {
        rand_nodes.push_back(info.rand_idx);
    }
    
    for (int i = 0; i < rand_nodes.size(); i++) {
        ListNode* node = m_dlist->m_go_to(i);
        if (rand_nodes[i] != -1) {
            if(node) node->rand = m_dlist->m_go_to(rand_nodes[i]);
        } else {
            node->rand = nullptr;
        }
    }

}

void DParser::Info(){
    for(auto inf: m_info_list){
        if(inf.msg.empty()){

        }else{
            std::cout << "Line number: " << inf.file_line_number << ": " << std::endl;
            std::cout << inf.msg <<  std::endl;
        }

    }
}

bool DParser::Serialize()
{

    std::cout << "File output: " << m_file_out_full_path << std::endl;
    std::fstream file(m_file_out_full_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << m_file_out_full_path << std::endl;
        return false;
    }

    uint32_t size = m_dlist->m_get_size();
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));

    // Проходим по списку и сериализуем каждый узел
    ListNode* current = m_dlist->m_get_head();
    for (uint32_t i = 0; i < size && current; ++i, current = current->next) {
        // data: длина строки (uint32_t) + строка (UTF-8)
        uint32_t data_len = current->data.length();
        file.write(reinterpret_cast<const char*>(&data_len), sizeof(data_len));
        file.write(current->data.c_str(), data_len);
        
        // rand_index: int32_t (-1 для nullptr)
        int32_t rand_idx = -1;
        if (current->rand) {
            // Находим индекс узла на который указывает rand
            ListNode* temp = m_dlist->m_get_head();
            for (int32_t j = 0; j < m_dlist->m_get_size() && temp; ++j, temp = temp->next) {
                if (temp == current->rand) {
                    rand_idx = j;
                    break;
                }
            }
        }
        file.write(reinterpret_cast<const char*>(&rand_idx), sizeof(rand_idx));
    }
    if (!file) {
        std::cerr << "Write error during serialization\n";
        return false;
    }
    
    std::cout << "Serialized " << size << " nodes to outlet.out\n";

    return true;

}

void DParser::PrintDlist(){
    m_dlist->m_print_forward();
}

void DParser::Set_file_in_path(const std::string& filename){
    m_file_in_full_path = filename;
}

void DParser::Set_file_out_path(const std::string& filename){
    m_file_out_full_path = filename;
}
