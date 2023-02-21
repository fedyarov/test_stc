#include <cstdint>
#include <memory>

template<class T>
struct ListNode {
    ListNode(T &&data): data(std::move(data)), next(nullptr)
    {};

    T take_data()
    {
        return std::move(data);
    }

    ListNode<T> *next;
    T data;
};

/*
 * We need to use custom single list implementation because 
 * std::forward_list invoke copy constructor on pop_front() and
 * std::unique_ptr<T> has requirement to T must be non CopyConstructible
 */
template<class T> 
class SingleList {
public:
    SingleList(): head(nullptr) 
    {}

    void push_front(T &&val) 
    {
        if (head == nullptr) {
            head = new ListNode(std::move(val));
        }
        else {
            auto new_head = new ListNode(std::move(val));
            new_head->next = head;
            head=new_head;
        }
    }

    T pop_front() 
    {
        if (head == nullptr) {
            std::cerr << "list is empty" << std::endl;
            std::terminate();
        }
        auto temp_head = head;
        auto return_value = temp_head->take_data();
        head = temp_head->next;
        
        delete(temp_head);
        return return_value;
    }

    bool is_empty()
    {
        return head == nullptr ? true : false;
    }
private:
    ListNode<T> *head;
};

/*
 * Stack implementation on single-linked list with arrays in nodes.
 * Node_size can be configuried depending on the input data.
 */
template<class T>
class Stack {
public:
    Stack(size_t node_size = 10): node_size(node_size), nodes() 
    {
        temp_node = make_node();
    }

    void push(T &&val) 
    {
        if (temp_node_current_size == node_size) {
            nodes.push_front(std::move(temp_node));

            temp_node = make_node();
            temp_node_current_size = 0;
        }
        temp_node[temp_node_current_size] = std::move(val);
        temp_node_current_size++;
    };

    T pop() 
    {
        if (temp_node_current_size == 0) {
            std::cerr << "stack is empty" << std::endl;
            std::terminate();
        }
        T return_value = std::move(temp_node[--temp_node_current_size]);
        if (temp_node_current_size == 0) {
            if (!nodes.is_empty()) {
                temp_node = nodes.pop_front();
                temp_node_current_size = node_size;
            }
        }
        return return_value;
    }

    bool is_empty()
    {
        return temp_node_current_size == 0 ? true: false;
    }
private:
    std::unique_ptr<T[]> make_node() 
    {
        std::unique_ptr<T[]> node(new T[node_size]);
        return node;
    }

    size_t node_size;
    size_t temp_node_current_size = 0;
    std::unique_ptr<T[]> temp_node;
    SingleList<std::unique_ptr<T[]>> nodes;
};

template<class T>
class Queue {
public:
    Queue(): s1(), s2() 
    {}

    void enqueu(T &&val)
    {
        s1.push(std::move(val));
    }

    /*
     * Caller has responsibility to check that queue is not empty before
     * invoke pop(). It can be changed by adding exceptions
     */
    T dequeue()
    {
        if (s2.is_empty()) {
            if (s1.is_empty()) {
                std::cerr << "queue is empty" << std::endl;
                std::terminate();
            }
            while (s1.is_empty() != true) {
                s2.push(s1.pop());
            }
        }
        return s2.pop();
    }

    bool is_empty() 
    {
        return s1.is_empty() && s2.is_empty();
    }
private:
    Stack<T> s1, s2;
};

int main(int argc, char const *argv[])
{

    return 0;
}