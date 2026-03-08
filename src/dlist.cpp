#include "dlist.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <algorithm>

DList::DList(): m_head(nullptr)
            , m_tail(nullptr)
            , m_temp(nullptr)
            , m_first(nullptr)
            , m_size(0){

}


DList::~DList() 
{
    ListNode* current = m_head;
    while (current != nullptr) {
    ListNode* next = current->next;
    delete current;
    current = next;
    }
}


/*
    Private Methods
*/

// Position access
ListNode* DList::m_get_head() const {
    return m_head;
}
ListNode* DList::m_get_tail() const {
    return m_tail;
}
int DList::m_get_size() const {
    return m_size;
}

// Insert
void DList::m_append(const std::string& data, ListNode* node) {

    if (m_size >= MAX_NODES) {
        std::cerr << "ERROR: Maximum nodes limit reached (" << MAX_NODES << ")\n";
        return;  // Не добавляем больше узлов
    }
    if(data.length() >= MAX_LENGTH){
        std::cerr << "ERROR: Maximum data length limit reached (" << MAX_LENGTH << ")\n";
        return;  // Не добавляем больше узлов
    }
    ListNode* newNode = new ListNode();
    newNode->data = data;
    newNode->rand = node;
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
void DList::m_prepend(const std::string& data, ListNode* node) {

    if (m_size >= MAX_NODES) {
        std::cerr << "ERROR: Maximum nodes limit reached (" << MAX_NODES << ")\n";
            return;  // Не добавляем больше узлов
    }
    if(data.length() >= MAX_LENGTH){
        std::cerr << "ERROR: Maximum data length limit reached (" << MAX_LENGTH << ")\n";
        return;  // Не добавляем больше узлов
    }

    ListNode* newNode = new ListNode();
    newNode->data = data;
    newNode->rand = node;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    if(m_head == nullptr){
        m_first = newNode;
        m_head = newNode;
        m_tail = newNode;
    }
    else{
        m_head->prev = newNode;
        newNode->next = m_head;
        m_head = newNode;
    }
    m_size++;
}
void DList::m_insert_after(const std::string& data, int pos, ListNode* node)
{
    if (m_size >= MAX_NODES) {
        std::cerr << "ERROR: Maximum nodes limit reached (" << MAX_NODES << ")\n";
        return;  // Не добавляем больше узлов
    }

    if(data.length() >= MAX_LENGTH){
        std::cerr << "ERROR: Maximum data length limit reached (" << MAX_LENGTH << ")\n";
        return;  // Не добавляем больше узлов
    }
    
    m_temp = this->m_go_to(pos);
    if(!m_temp){
        return;
    }
    ListNode* newNode = new ListNode();
    newNode->data = data;
    newNode->rand = node;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    newNode->prev = m_temp;
    newNode->next = m_temp->next;
    m_temp->next = newNode;

    if(newNode->next != nullptr){
        newNode->next->prev = newNode;
    }
    else{
        m_tail = newNode;
    }
    m_size++;

}

void DList::m_insert_before(const std::string& data, int pos, ListNode* node){

    if (m_size >= MAX_NODES) {
        std::cerr << "ERROR: Maximum nodes limit reached (" << MAX_NODES << ")\n";
        return;  // Не добавляем больше узлов
    }
    if(data.length() >= MAX_LENGTH){
        std::cerr << "ERROR: Maximum data length limit reached (" << MAX_LENGTH << ")\n";
        return;  // Не добавляем больше узлов
    }
    m_temp = this->m_go_to(pos);
    if(!m_temp){
        return;
    }
    ListNode* newNode = new ListNode();
    newNode->data = data;
    newNode->rand = node;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    newNode->prev = m_temp->prev;
    newNode->next = m_temp;
    m_temp->prev = newNode;

    if(newNode->prev != nullptr){
        newNode->prev->next = newNode;
    }
    else{
        m_head = newNode;
    }
    m_size++;
}

// Remove
void DList::m_remove_head() {
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
void DList::m_remove_tail() {
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
void DList::m_remove_position(int pos) {
    // If invalid position
    if (pos < 0 || pos >= m_size) {
        std::cout <<"Please enter a valid position (from 0 to " << m_size-1 << ")"  << std::endl;
    }

    else if(pos == 0) {
        m_remove_head();
    }
    else if(pos == m_size - 1) { 
        m_remove_tail();
    }  
    else {
        m_first = m_head;
        while(pos-- > 0) {
            m_first = m_first->next;
            if(m_first == nullptr) { 
            std::cout << "There is no node " << std::endl;
            return;
            }
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
ListNode* DList::m_find(const std::string& data){
    if (m_head == nullptr) {
        std::cout <<"DList is empty" << std::endl;
        return nullptr;
    }  
    m_first = m_head;
    while(m_first){
        if(m_first->data == data) return m_first;
        m_first = m_first->next;
    }   
    return nullptr; 
} 

ListNode* DList::m_go_to(int pos){
    if (pos < 0 || pos > m_size - 1) {
        std::cout <<"Please enter a valid position (from 0 to " << m_size-1 << ")"  << " Pos for rand: " << pos << std::endl;
        return nullptr;
    }  
    if(pos == m_size - 1){
        return m_tail;
    } 
    if(pos == 0){
        return m_head;
    }   
    m_first = m_head;
    while(pos-- > 0){
        m_first = m_first->next;
        if(m_first == nullptr){
            std::cout << "There is no such a node. " << std::endl;
            return m_first;
        }
    }   
    return m_first; 
}  

// Traversal helpers
void DList::m_print_forward() const {
    if(m_head == nullptr)
    {
        std::cout << "List is empty" << std::endl;
    }
    ListNode* current = m_head;
    while (current != nullptr) {
        std::cout << current->data << std::endl;
        std::cout << "Rand: " << current->rand << std::endl;
        current = current->next;
    }
}
void DList::m_print_backward() const {
    if(m_head == nullptr)
    {
        std::cout << "List is empty" << std::endl;
    }
    ListNode* current = m_tail;
    while (current != nullptr) {
    std::cout << current->data << std::endl;
    current = current->prev;
    }

}



