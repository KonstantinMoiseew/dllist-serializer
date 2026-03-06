#include "dlist.hpp"

DList::DList(): m_head(nullptr)
            , m_tail(nullptr)
            , m_temp(nullptr)
            , m_first(nullptr)
            , m_size(0)
            , m_file_full_path("")
{}


DList::~DList() 
{
    ListNode* current = m_head;
    while (current != nullptr) {
    ListNode* next = current->next;
    delete current;
    current = next;
    }
}

bool DList::Serialize() const
{}

bool DList::Deserialize()
{}

/*
    Private Methods
*/

// Position access
ListNode* DList::m_get_head() const
{}
ListNode* DList::m_get_tail() const
{}
int DList::m_get_size() const
{}

// Insert
void DList::m_append(std::string& data)
{}
void DList::m_prepend(std::string& data)
{}
void DList::m_insert_after(std::string& data, int pos)
{}

void DList::m_insert_before(std::string& data, int pos)
{}

// Remove
void DList::m_remove_head()
{}
void DList::m_remove_tail()
{}
void DList::m_remove_poition(int pos)
{}

// Search/position
ListNode* DList::m_find(const std::string& data)
{} 
ListNode* DList::m_go_to(int pos)
{}  

// Traversal helpers
void DList::m_print_forward() const
{}
void DList::m_print_backward() const
{}

bool DList::m_read_file(const std::string& filename)
{}

bool DList::m_write_file(const std::string& filename) const
{}

void DList::m_set_file_path(const std::string& filename)
{}

