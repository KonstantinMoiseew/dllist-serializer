#ifndef DLIST_HPP
#define DLIST_HPP
#include "listnode.hpp"
#include <vector>

class DList {
    public:
        DList(); // Empty List
        ~DList(); // Delete all nodes

        std::string GetErrMsg();
        void ClearErrMsg();

        // Position access
        ListNode* Get_head() const;
        ListNode* Get_tail() const;
        int Get_size() const;


        // Insert
        void Append(const std::string& data, ListNode* node = nullptr);
        void Prepend(const std::string& data, ListNode* node = nullptr);
        void Insert_after(const std::string& data, int pos, ListNode* node = nullptr);
        void Insert_before(const std::string& data, int pos, ListNode* node = nullptr);

        // Remove
        void Remove_head();
        void Remove_tail();
        void Remove_position(int pos);

        // Search/position
        ListNode* Find(const std::string& data);  
        ListNode* Go_to(int pos);  

        // Traversal helpers
        void Print_forward() const; 
        void Print_backward() const;
        std::string m_error_msg;

        private:
      
        /*

        */
        ListNode* m_head;
        ListNode* m_tail;
        ListNode* m_temp;
        ListNode* m_first;

        std::vector<ListNode*> m_nodes;

        
        int m_size = 0;

        static constexpr size_t MAX_NODES = 1000000; 
        static constexpr size_t MAX_LENGTH = 1000;
};

#endif // DLIST_HPP



