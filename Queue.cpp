#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;


template <typename T>
struct Node {
    T data;
    Node* next;
    //constructor that initializes the node with data
    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class Stack {
private:
    Node<T>* head;
    int size;           
    int current_size;

public:
    Stack(int s = -1) {
        head = nullptr;
        size = s;
        current_size = 0;
    }

    //pushing an element on top of the stack
    void push(T data) {
        if (size != -1 && current_size >= size) {
            cout << "Stack is full" << endl;
            return;
        }
        Node<T>* new_node = new Node<T>(data);
        new_node->next = head;
        head = new_node;
        current_size++;
    }

    //popping an element from the stack
    T pop() {
        if (head == nullptr) {
            cout << "Stack is empty" << endl;
            return T();
        }
        Node<T>* temp = head;
        T popped = head->data;
        head = head->next;
        delete temp;
        current_size--;
        return popped;
    }

    //we check if the stack is empty
    bool isEmpty() {
        return head == nullptr;
    }

    //this function gets the number of elements in the stack
    int getCurrentSize() {
        return current_size;
    }
};


//queue implemented using 2 stacks
template <typename T>
class Queue {
private:
    Stack<T> in_stack;//we use it for enqueue
    Stack<T> out_stack;//dequeue

public:
    //constructor that creates the stacks
    Queue(int capacity = 100) : in_stack(capacity), out_stack(capacity) {}

    //pushing the elements onto the stack
    void enqueue(T item) {
        in_stack.push(item);
    }

    //we pop the elements out of out_stack and if it is empty
    //we move the elements
    T dequeue() {
        if (out_stack.isEmpty()) {
            while (!in_stack.isEmpty()) {
                out_stack.push(in_stack.pop());
            }
        }
        return out_stack.pop();
    }

    bool isEmpty() {
        return in_stack.isEmpty() && out_stack.isEmpty();
    }
};

int main() {
    Queue<float> q(50);//creating our queue


    auto start = high_resolution_clock::now();
    q.enqueue(1.5);
    auto end = high_resolution_clock::now();
    cout << "We enqueue 1.5 time: " 
         << duration<double, micro>(end - start).count() << "milisec" << endl;

    
    start = high_resolution_clock::now();
    q.enqueue(2.5);
    end = high_resolution_clock::now();
    cout << "We enqueue 2.5 time: " 
         << duration<double, micro>(end - start).count() << "milisec" << endl;

   
    start = high_resolution_clock::now();
    q.enqueue(3.5);
    end = high_resolution_clock::now();
    cout << "We enqueue 3.5 time: " 
         << duration<double, micro>(end - start).count() << "milisec" << endl;

   
    start = high_resolution_clock::now();
    cout << "We dequeued: " << q.dequeue() << endl;
    end = high_resolution_clock::now();
    cout << "Dequeue time: " 
         << duration<double, micro>(end - start).count() << "milisec" << endl;

    
    start = high_resolution_clock::now();
    cout << "We dequeued: " << q.dequeue() << endl;
    end = high_resolution_clock::now();
    cout << "Dequeue time: " 
         << duration<double, micro>(end - start).count() << " milisec" << endl;

    
    start = high_resolution_clock::now();
    q.enqueue(4.5);
    end = high_resolution_clock::now();
    cout << "We enqueue 4.5 time: " 
         << duration<double, micro>(end - start).count() << "milisec" << endl;

    
    start = high_resolution_clock::now();
    cout << "We dequeued: " << q.dequeue() << endl;
    end = high_resolution_clock::now();
    cout << "Dequeue time: " 
         << duration<double, micro>(end - start).count() << " milisec" << endl;

    // Dequeue (possibly empty)
    start = high_resolution_clock::now();
    cout << "We dequeued: " << q.dequeue() << endl;
    end = high_resolution_clock::now();
    cout << "Dequeue time: " 
         << duration<double, micro>(end - start).count() << "milisec" << endl;

    return 0;
}
