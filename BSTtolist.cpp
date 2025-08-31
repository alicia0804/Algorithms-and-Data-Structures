#include <iostream>

struct treenode {
    int val;
    treenode* left;
    treenode* right;

    //constructor for tree node 
    treenode(int x) {
        val = x;        
        left = nullptr; 
        right = nullptr; 
    }
};

//node for a linked list
struct listnode {
    int val;
    listnode* next;

    listnode(int x) : val(x), next(nullptr) {}
};

class convertinglist {

private:
    void traverse(treenode* node, listnode*& current) {
        if (!node) return;
        //recursive function to the left subtree
        traverse(node->left, current);
        //after the left subtree is processed we add the current element in the
        //linked list
        current->next = new listnode(node->val);
        current = current->next;
        traverse(node->right, current);
    }
public:
    listnode* bsttolist(treenode* root) {
        if (!root) return nullptr;

        //node to act as the head of the list
        listnode headnode(0);
        listnode* current = &headnode;

        //performing traversing
        traverse(root, current);

        return headnode.next;
    }
};

void print(listnode* node) {
    while (node) {
        std::cout << node->val << " ";
        node = node->next;
    }
    std::cout << "nullptr\n";
}

int main() {
    treenode* root = new treenode(5);
    root->left = new treenode(1);
    root->right = new treenode(8);
    root->left->left = new treenode(0);  
    root->left->right = new treenode(4); 
    root->right->left = new treenode(6); 
    root->right->right = new treenode(10);
    convertinglist s;
    listnode* result = s.bsttolist(root);

    print(result);

    return 0;
}
