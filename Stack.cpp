#include <iostream>
#include <chrono> 

//we declare a template class to use any data
template <typename T>
class Stack {
private:
    struct StackNode {       
        T data;
        StackNode* next;
    };
    StackNode* top;          
    int size;                 
    int current_size;         

public:
    //this constructor sets the new size for the stack
    Stack(int new_size) {
        size = new_size;
        top = nullptr;
        current_size = 0; //we don't have elements yet
    }

    //default constructor for when the size is not set
    Stack() {
        size = -1;
        top = nullptr;
        current_size = 0;
    }

    //if we have the size we check for overflow
    void push(T x) {         
        if (size != -1 && current_size >= size) {
            std::cout << "The stack is overflowing! " << x << std::endl;
            return;
        }
        //we create a new node and assign the data to it
        //and we update the top while increasing the size 
        StackNode* new_node = new StackNode();
        new_node->data = x;
        new_node->next = top;//pointing the new node to the current top
        top = new_node;
        current_size++;
    }

    T pop() {               
        if (isEmpty()) {
            std::cout << "Stack underflow!" << std::endl;
            return T(); 
        }
        StackNode* temp = top;
        T popped_data = temp->data;
        top = top->next;
        delete temp;
        current_size--;
        return popped_data;
    }

    bool isEmpty() {          
        return top == nullptr;
    }
};

int main() {
    Stack<int> s(5); 

    //we measure time for push operation
    auto start_push = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 5; ++i) {
        s.push(i);
    }
    auto end_push = std::chrono::high_resolution_clock::now();

    //we measure time for isEmpty operation
    auto start_empty = std::chrono::high_resolution_clock::now();
    bool empty = s.isEmpty();
    auto end_empty = std::chrono::high_resolution_clock::now();

    // Optional: print to use the variable and avoid warning
    std::cout << "Stack empty? " << (empty ? "Yes" : "No") << std::endl;

    //we masure time for pop operation
    auto start_pop = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 5; ++i) {
        s.pop();
    }
    auto end_pop = std::chrono::high_resolution_clock::now();

    std::cout << "Time for push operations: "
              << std::chrono::duration<double, std::micro>(end_push - start_push).count()
              << " milisec" << std::endl;

    std::cout << "Time for isEmpty operation: "
              << std::chrono::duration<double, std::micro>(end_empty - start_empty).count()
              << "milisec" << std::endl;

    std::cout << "Time for pop operations: "
              << std::chrono::duration<double, std::micro>(end_pop - start_pop).count()
              << " milisec" << std::endl;

    return 0;
}
