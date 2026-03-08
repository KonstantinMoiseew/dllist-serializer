#include <iostream>
#include "dlist.hpp"
#include "dparser.hpp"

int main(int argc, char* argv[])
{
    std::string input_file, output_file;
    for (int i = 0; i < argc; i++) {  
        std::string arg = argv[i];  
        
        if (arg == "-in" && i + 1 < argc) {
            input_file = argv[i + 1];
            i++;  
        }
        if (arg == "-out" && i + 1 < argc) {
            output_file = argv[i + 1];
            i++;  
        }
    }
    
    DParser dparser;
    if(!input_file.empty()){
        dparser.Set_file_in_path(input_file);
    }
    if(!output_file.empty()){
        dparser.Set_file_out_path(output_file);
    }
    dparser.Parse();
    dparser.Info();
    dparser.Serialize();
    dparser.PrintDlist();
}