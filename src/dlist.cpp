#include "dlist.hpp"
#include <iostream>

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

bool DList::Serialize()
{

    this->m_prepend("apple");
    this->m_prepend("banana");
    this->m_prepend("nut");
    this->m_append("icecream");

    this->m_print_forward();

    this->m_remove_position(2);

    this->m_print_forward();

    return true;

}

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
void DList::m_append(const std::string& data)
{
    ListNode* newNode = new ListNode();
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    if(m_head == nullptr)
    {
        m_first = newNode;
        m_head = newNode;
        m_tail = newNode;
    }
    else
    {
        newNode->prev = m_tail;
        m_tail->next = newNode;
        m_tail = newNode;
    }
    m_size++;
}
void DList::m_prepend(const std::string& data)
{
    ListNode* newNode = new ListNode();
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    if(m_head == nullptr)
    {
        m_first = newNode;
        m_head = newNode;
        m_tail = newNode;
    }
    else
    {
        m_head->prev = newNode;
        newNode->next = m_head;
        m_head = newNode;
    }
    m_size++;
}
void DList::m_insert_after(const std::string& data, int pos)
{}

void DList::m_insert_before(const std::string& data, int pos)
{}

// Remove
void DList::m_remove_head()
{
    if(m_head == nullptr) 
    {
        std::cout << "Can not remove! The list is empty." << std::endl;
        return;
    }
    m_temp = m_head;
    m_head = m_head->next;
    if(m_head != nullptr) {
        m_head->prev = nullptr;   
    } 
    else {
        m_tail = nullptr;        
        m_first = nullptr;
    }
    m_size--;
    delete m_temp;
}
void DList::m_remove_tail()
{
    if(m_head == nullptr) 
    {
        std::cout << "Can not remove! The list is empty." << std::endl;
        return;
    }
    
    m_temp = m_tail;
    m_tail = m_tail->prev;
    if(m_tail != nullptr)
        m_tail->next = nullptr;
    else {
        m_head = nullptr;        
        m_first = nullptr;
    }

    m_size--;
    delete m_temp;
}
void DList::m_remove_position(int pos)
{
    // If invalid position
    if (pos < 1 || pos > m_size) {
        std::cout <<"Please enter a valid position" << std::endl;
    }

    else if(pos == 1) {
        m_remove_head();
    }
    

    else if(pos == m_size) { 
        m_remove_tail();
    }
    
    else {
        m_first = m_head;
        while(pos-- > 1) {
            m_first = m_first->next;
        }
        if(m_first == nullptr) { 
            std::cout << "There is no node " << std::endl;
            return;
        }
        ListNode* prev = m_first->prev;
        ListNode* next = m_first->next;
        prev->next = next;
        next->prev = prev;
        delete m_first;
        m_size--;
    }   
}

// Search/position
ListNode* DList::m_find(const std::string& data)
{} 
ListNode* DList::m_go_to(int pos)
{}  

// Traversal helpers
void DList::m_print_forward() const
{
    if(m_head == nullptr)
    {
        std::cout << "List is empty" << std::endl;
    }
    ListNode* current = m_head;
    while (current != nullptr) {
    std::cout << current->data << std::endl;
    current = current->next;
    }
}
void DList::m_print_backward() const
{}

bool DList::m_read_file(const std::string& filename)
{}

bool DList::m_write_file(const std::string& filename) const
{}

void DList::m_set_file_path(const std::string& filename)
{}

