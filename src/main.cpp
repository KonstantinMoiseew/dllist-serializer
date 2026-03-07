#include <iostream>
#include "dlist.hpp"

int main()
{
    DList* list = new DList();
    //list->Set_file_path("/home/const/repos/double_linked_list/dllist-serializer/res/inlet.in");
    //list->Set_file_path("/home/const/repos/double_linked_list/dllist-serializer/res/outlet.out");
    list->ReadFileIn();
    list->Serialize();
    
}