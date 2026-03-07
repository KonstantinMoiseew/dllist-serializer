#ifndef DLIST_HPP
#define DLIST_HPP
#include "listnode.hpp"

class DList {
    public:
        DList(); // Empty List
        ~DList(); // Delete all nodes

        bool Serialize();
        bool Deserialize();
        bool ReadFileIn();
        void Set_file_in_path(const std::string& filename);
        void Set_file_out_path(const std::string& filename);


    private:

        // Position access
        ListNode* m_get_head() const;
        ListNode* m_get_tail() const;
        int m_get_size() const;


        // Insert
        void m_append(const std::string& data, ListNode* node = nullptr);
        void m_prepend(const std::string& data, ListNode* node = nullptr);
        void m_insert_after(const std::string& data, int pos, ListNode* node = nullptr);
        void m_insert_before(const std::string& data, int pos, ListNode* node = nullptr);

        // Remove
        void m_remove_head();
        void m_remove_tail();
        void m_remove_position(int pos);

        // Search/position
        ListNode* m_find(const std::string& data);  
        ListNode* m_go_to(int pos);  

        // Traversal helpers
        void m_print_forward() const; 
        void m_print_backward() const;

        // File 
        bool m_read_file(const std::string& filename);
        bool m_write_file(const std::string& filename) const;
        
        /*

        */
        ListNode* m_head;
        ListNode* m_tail;
        ListNode* m_temp;
        ListNode* m_first;

        int m_size = 0;

        std::string m_file_in_full_path;
        std::string m_file_out_full_path;

        static constexpr size_t MAX_NODES = 1000000; 
        static constexpr size_t MAX_LENGTH = 1000;
};

#endif // DLIST_HPP



