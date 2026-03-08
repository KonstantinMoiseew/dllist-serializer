#include "dparser.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

DParser::DParser(){}
DParser::~DParser(){}
void DParser::ReadFileIn(){
    int fd = open("/home/const/repos/double_linked_list/dllist-serializer/res/inlet.in", O_RDONLY);
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
