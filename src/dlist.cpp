#include "dlist.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

DList::DList(): m_head(nullptr)
            , m_tail(nullptr)
            , m_temp(nullptr)
            , m_first(nullptr)
            , m_size(0){
    std::error_code ec;
    std::filesystem::path canonical_path = std::filesystem::canonical("./res/inlet.in", ec);
    if (ec) {
        std::cerr << "Canonical failed: " << ec.message() << std::endl;
        m_file_full_path = "../res/inlet.in";  // Fallback
    } else {
        m_file_full_path = canonical_path.string();
    }
    std::cout << "Working dir: " << std::filesystem::current_path() << std::endl; //working dir (pwd) inherits from parent process.
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

bool DList::Serialize()
{

    /*
    this->m_prepend("apple");
    this->m_prepend("banana");
    this->m_prepend("nut");
    this->m_append("icecream");

    ListNode* node = this->m_go_to(3);
    std::cout << "ListNode[3]: " << node->data << std::endl;
    node = m_find("nut");
    std::cout << "ListNode with a certain data nut: " << node->data << std::endl;
    this->m_print_forward();
    m_insert_after("milk", 2);
    std::cout << "###### forward: " << std::endl;
    this->m_print_forward();
    std::cout << "###### backward: " << std::endl;
    this->m_print_backward();
    std::cout << "#######" << std::endl;

    std::cout << "Insertion before:  " << std::endl;
    this->m_insert_before("bread", 3);
    std::cout << "###### forward: " << std::endl;
    this->m_print_forward();
    std::cout << "#######" << std::endl;


    this->m_remove_position(2);

    this->m_print_forward();

    this->m_print_backward();
    */


    this->m_print_forward();

    return true;

}

bool DList::Deserialize(){
    std::cout << "File: " << m_file_full_path << std::endl;
    std::fstream file(m_file_full_path);
    if (!file.is_open()) {
    std::cerr << "Failed to open " << m_file_full_path << std::endl;
    return false;
    }

    std::string line;
    std::vector<int> rand_nodes;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
    
        std::istringstream iss(line);
        std::string data, index_str;
        if (!std::getline(iss, data, ';') || !std::getline(iss, index_str, ';')) {
            continue; 
        }
    
        int rand_idx;
        try {
            rand_idx = std::stoi(index_str);
        } catch (const std::exception& e) {
            std::cerr << "Invalid index '" << index_str << "': " << e.what() <<" of data: " << data << std::endl;
            std::cout << "Проверьте правильность формата входного файла. " << std::endl;
            rand_idx = -1;
        }

        rand_nodes.push_back(rand_idx);

        m_append(data);
    }
    ListNode* node = nullptr;
    for (int i = 0; i < rand_nodes.size(); i++){
        node = m_go_to(i);
        if(rand_nodes[i] != -1)
            node->rand = m_go_to(rand_nodes[i]);
        else
            node->rand = nullptr;

    }
    return true;
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
        std::cout <<"Please enter a valid position (from 0 to )" << m_size-1 << ")"  << std::endl;
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

bool DList::m_read_file(const std::string& filename){

}

bool DList::m_write_file(const std::string& filename) const
{}

void DList::Set_file_path(const std::string& filename){
    m_file_full_path = filename;
}

