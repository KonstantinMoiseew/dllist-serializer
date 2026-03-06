#ifndef DLIST_HPP
#define DLIST_HPP
#include "listnode.hpp"

class DList {
    public:
        DList(); // Empty List
        ~DList(); // Delete all nodes

        bool Serialize(const std::string& filename) const;
        bool Deserialize(const std::string& filename);


    private:

        // Position access
        ListNode* m_head() const;
        ListNode* m_tail() const;
        int m_size() const;


        // Insert
        void m_append(std::string& data);
        void m_prepend(std::string& data);
        void m_insert_after(std::string& data, int pos);
        void m_insert_before(std::string& data, int pos);

        // Remove
        void m_remove_head();
        void m_remove_tail();
        void m_remove_poition(int pos);

        // Search/position
        ListNode* m_find(const std::string& data);  
        ListNode* m_go_to(int pos);  

        // Traversal helpers
        void m_print_forward() const; 
        void m_print_backward() const;


        /*

        */
        ListNode* m_head = nullptr;
        ListNode* m_tail = nullptr;
        ListNode* m_temp = nullptr;
        ListNode* m_first = nullptr;

        int m_size = 0;
};

#endif // DLIST_HPP



