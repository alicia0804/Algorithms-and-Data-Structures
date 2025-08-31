#include <iostream> 
#include <list>    
using namespace std; 

//we define the color for RB Tree nodes
enum Color {
    RED,
    BLACK
};

struct Node {
    int data;              
    Color color;    
    //the pointers to the parent and left+right children  
    Node *left, *right, *parent; 
};

class RedBlackTree {
private:
    Node *root; 

protected:
    void rotateLeft(Node *&elem) {
        Node *y = elem->right;//we store the right child
        elem->right = y->left;//we turn y's left subtree into elem's right subtree
        if (y->left != NULL) {
            y->left->parent = elem;  
        }
        y->parent = elem->parent;//we link the parents

        if (elem->parent == NULL) {
            root = y;                
        } else if (elem == elem->parent->left) {
            elem->parent->left = y; 
        } else {
            elem->parent->right = y; 
        }
        y->left = elem;//we put the element on y's left and update elem parent
        elem->parent = y;        
    }

    void rotateRight(Node *&elem) {
        Node *y = elem->left; 
        //we turn y's right subtree into elem's left subtree       
        elem->left = y->right;
        if (y->right != NULL) {
            y->right->parent = elem; 
        }
        y->parent = elem->parent;//we link the parents

        if (elem->parent == NULL) {
            root = y;          
        } else if (elem == elem->parent->left) {
            elem->parent->left = y; 
        } else {
            elem->parent->right = y; 
        }
        y->right = elem;            
        elem->parent = y;         
    }

    //function to insert a node into the BST without 
    //messing up the RB properties
    Node *binarytreeinsert(Node *&root, Node *&elem) {
        if (root == NULL) {
            return elem;             
        }
        if (elem->data < root->data) {
            root->left = binarytreeinsert(root->left, elem); 
            root->left->parent = root; 
        } else if (elem->data > root->data) {
            root->right = binarytreeinsert(root->right, elem); 
            root->right->parent = root; 
        }
        return root; 
    }

    //this function checks if a node is red
    bool isRed(Node *elem) {
        return (elem != NULL && elem->color == RED);
    }

    //reparing the tree after insertion to maintain RB properties
    void RBInsertFix(Node *&elem) {
        while (isRed(elem->parent)) { //while parent is red
            if (elem->parent == elem->parent->parent->left) { //if parent is left child
                Node *uncle = elem->parent->parent->right;//we get the uncle
                Node *grandparent = elem->parent->parent;
                //if the uncle is red we recolor uncle, grandparent and move up
                //the tree
                if (isRed(uncle)) { 
                    elem->parent->color = BLACK; 
                    uncle->color = BLACK;       
                    grandparent->color = RED;   
                    elem = grandparent;          
                } else {
                    //if the element is right child we rotate left
                    if (elem == elem->parent->right) { 
                        elem = elem->parent;
                        rotateLeft(elem);            
                    }
                    //if the elem is left child we rotate right
                    elem->parent->color = BLACK;
                    grandparent->color = RED;
                    rotateRight(grandparent);
                }
            } else { 
                Node *grandparent = elem->parent->parent;
                Node *uncle = elem->parent->parent->left;
                if (isRed(uncle)) {
                    elem->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    elem = grandparent;
                } else {
                    if (elem == elem->parent->left) {
                        elem = elem->parent;
                        rotateRight(elem);
                    }
                    elem->parent->color = BLACK;
                    grandparent->color = RED;
                    rotateLeft(grandparent);
                }
            }
        }
        root->color = BLACK; 
    }

    Node *helpermin(Node *elem) {
        while (elem->left != NULL) {
            elem = elem->left;
        }
        return elem;
    }
    Node *helpermax(Node *elem) {
        while (elem->right != NULL) {
            elem = elem->right;
        }
        return elem;
    }
    Node *helpersearch(Node *elem, int data) {
        while (elem != NULL && data != elem->data) {
            if (data < elem->data) {
                elem = elem->left;
            } else {
                elem = elem->right;
            }
        }
        return elem;
    }

    //with this function we replace subtree u with subtree v
    void transplant(Node *u, Node *v) {
        if (u->parent == NULL) {
            root = v; 
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != NULL) {
            v->parent = u->parent; 
        }
    }

    //we fix RB proprieties after deletion
    void Deletefix(Node *&elem) {
        Node *w;
        while (elem != root && elem->color == BLACK) {
            if (elem == elem->parent->left) {
                w = elem->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    elem->parent->color = RED;
                    rotateLeft(elem->parent);
                    w = elem->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    elem = elem->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = elem->parent->right;
                    }
                    w->color = elem->parent->color;
                    elem->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotateLeft(elem->parent);
                    elem = root;
                }
            } else {
                w = elem->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    elem->parent->color = RED;
                    rotateRight(elem->parent);
                    w = elem->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    elem = elem->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = elem->parent->left;
                    }
                    w->color = elem->parent->color;
                    elem->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateRight(elem->parent);
                    elem = root;
                }
            }
        }
        elem->color = BLACK;
    }

    void helpercolor(Node *elem) {
        if (elem->color == RED) {
            cout << "Red";
        } else {
            cout << "Black";
        }
    }

    void helperprint(Node *&elem) {
        cout << elem->data;     
        helpercolor(elem);    
        cout << "  ";
        if (elem->left != NULL) {
            helperprint(elem->left); 
        }
        if (elem->right != NULL) {
            helperprint(elem->right); 
        }
    }

public:
    RedBlackTree() {
        root = NULL;
    }

    //constructr to insert node with a given value
    void insert(int val) {
        Node *elem = new Node;       
        elem->data = val;
        elem->color = RED;//always having the new node red
        elem->left = elem->right = elem->parent = NULL;

        if (root == NULL) {
            root = elem;             
        } else {
            binarytreeinsert(root, elem); 
        }
        RBInsertFix(elem);             
    }

    //we find the predecessor of a given node
    Node *predecessor(Node *&elem) {
        if (elem->left != NULL) {
            return helpermax(elem->left);
        }
        Node *y = elem->parent;
        while (y != NULL && elem == y->left) {
            elem = y;
            y = y->parent;
        }
        return y;
    }

    //we find successor of a given node
    Node *successor(Node *&elem) {
        if (elem->right != NULL) {
            return helpermin(elem->right);
        }
        Node *y = elem->parent;
        while (y != NULL && elem == y->right) {
            elem = y;
            y = y->parent;
        }
        return y;
    }

    Node *getMinimum() {
        return helpermin(root);
    }

    Node *getMaximum() {
        return helpermax(root);
    }

    Node *search(int data) {
        return helpersearch(root, data);
    }

    void Delete(Node *&elem) {
        Node *y = elem;              
        Color Ycolor = y->color;      
        Node *x;                    

        if (elem->left == NULL) {
            x = elem->right;
            transplant(elem, elem->right);
        } else if (elem->right == NULL) {
            x = elem->left;
            transplant(elem, elem->left);
        } else {
            y = helpermin(elem->right);
            Ycolor = y->color;
            x = y->right;
            if (y->parent == elem) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = elem->right;
                y->right->parent = y;
            }
            transplant(elem, y);
            y->left = elem->left;
            y->left->parent = y;
            y->color = elem->color;
        }
        if (Ycolor == BLACK) {
            Deletefix(x);
        }
    }

    //function to print the tree
    void print() {
        helperprint(root);
        cout << endl;
    }
};

int main(){

    RedBlackTree tree;
    tree.insert(44);
    tree.insert(13);
    tree.insert(7);
    tree.insert(22);
    tree.insert(37);
    tree.insert(16);
    cout<<endl;
    cout<<"Tree after insertion (preorder traversal)"<<endl;
    tree.print();
    cout<<endl;
    cout<<"deleting the node 22"<<endl;
    Node *node = tree.search(22);
    tree.Delete(node);
    tree.print();
}
