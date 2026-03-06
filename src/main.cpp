#include <iostream>
#include "dlist.hpp"

int main()
{
    std::cout << "Hello world!" << std::endl;
    DList* list = new DList();
    list->Serialize();
    
}