#ifndef DLIST_HPP
#define DLIST_HPP
#include "listnode.hpp"

class DList {
    public:
        DList(); // Empty List
        ~DList(); // Delete all nodes

        bool Serialize() const;
        bool Deserialize();


    private:

        // Position access
        ListNode* m_get_head() const;
        ListNode* m_get_tail() const;
        int m_get_size() const;


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

        // File 
        bool m_read_file(const std::string& filename);
        bool m_write_file(const std::string& filename) const;
        void m_set_file_path(const std::string& filename);


        /*

        */
        ListNode* m_head;
        ListNode* m_tail;
        ListNode* m_temp;
        ListNode* m_first;

        int m_size = 0;

        std::string m_file_full_path;
};

#endif // DLIST_HPP



