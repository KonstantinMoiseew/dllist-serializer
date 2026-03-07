#include <iostream>
#include "dlist.hpp"

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
    
    DList* list = new DList();
    if(!input_file.empty()){
        list->Set_file_in_path(input_file);
    }
    if(!output_file.empty()){
        list->Set_file_out_path(output_file);
    }
    list->ReadFileIn();
    list->Serialize();
    
}