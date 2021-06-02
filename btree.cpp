/*
    Created By: Thomas Osgood
    
    Description:
        Simple binary tree program.
        
    To-Do:
        1) Put Class in separate file and create custom header. 
            i)  btree.h
        2) Add sort/balance function.
        
    To Compile:
    g++ -o <binary_name> btree.cpp
*/

// ------- REQUIRED Includes -------
#include <iostream>
#include <limits>

/*
    Create Structure For Node Object
*/
struct node {
    int key_val;
    node *left;
    node *right;
};

/*
    Function Prototypes
*/
void printChar(char c = '-', int n = 40);

/*
    Define Binary Tree Class
*/
class btree {
    public:
        btree(); // binary tree initializer
        ~btree(); // binary tree destroyer
        
        void destroy_tree();
        void display_tree();
        void display_tree_rev();
        void insert(int key);
        int maxKey();
        int minKey();
        node *search(int key);
        
    private:
        void destroy_tree(node *leaf);
        void display_tree(node *leaf);
        void display_tree_rev(node *leaf);
        void insert(int key, node *leaf);
        int maxKey(node *leaf);
        int minKey(node *leaf);
        node *search(int key, node *leaf);
        
        node *root;
};

/*
    Class Functions
*/

// --------- BEGIN Class Functions --------------

/*
Function Name: btree
Description:
    Binary tree function that will be called when the tree
    is allocated/created.
Input(s):
    None
Return(s):
    None
*/
btree::btree() {
    std::cout << "[+] Initializing BTREE" << std::endl;
    root = NULL;
}

/*
Function Name: ~btree
Description:
    Binary tree function that will be called when the tree
    is deallocated/destroyed.
Input(s):
    None
Return(s):
    None
*/
btree::~btree() {
    std::cout << "[-] Destroying BTREE" << std::endl;
    destroy_tree();
}

// --------- PRIVATE Class Functions --------------

/*
Function Name: destroy_tree
Description:
    Private function called when the tree is going to be
    destroyed.  Will recursively go through each node and
    subnode and delete the entire tree.
Input(s):
    leaf - node pointer. current leaf/node to delete.
Return(s):
    None
*/
void btree::destroy_tree(node *leaf) {
    if (leaf != NULL) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

/*
Function Name: display_tree
Description:
    Private function designed to display the binary tree.
    
    Displays the tree in a left to right (low to high)
    order, checking for left nodes first, then displaying
    the current node, then checking for right nodes.
Input(s):
    leaf - node pointer. current leaf/node to display.
Return(s):
    None
*/
void btree::display_tree(node *leaf) {
    if (leaf->left != NULL) display_tree(leaf->left);
    std::cout << leaf->key_val << std::endl;
    if (leaf->right != NULL) display_tree(leaf->right);
}

/*
Function Name: display_tree_rev
Description:
    Private function designed to display the binary tree
    in reverse order.
    
    Displays the tree in a right to left (high to low)
    order, checking for right nodes first, then displaying
    the current node, then checking for left nodes.
Input(s):
    leaf - node pointer. current leaf/node to display.
Return(s):
    None
*/
void btree::display_tree_rev(node *leaf) {
    if (leaf->right != NULL) display_tree_rev(leaf->right);
    std::cout << leaf->key_val << std::endl;
    if (leaf->left != NULL) display_tree_rev(leaf->left);
}

/*
Function Name: insert
Description:    
    Private BTREE function to insert key value
    into binary tree.
Input(s):
    key - integer value to insert.
    leaf - node pointer. reference to current spot in tree.
Return(s):
    None
*/
void btree::insert(int key, node *leaf) {
    if (key <= leaf->key_val) {
        if (leaf->left != NULL)
            insert(key, leaf->left);
        else {
            leaf->left = new node;
            leaf->left->key_val = key;
            leaf->left->left = NULL;
            leaf->left->right = NULL;
        }
    } else {
        if (leaf->right != NULL)
            insert(key, leaf->right);
        else {
            leaf->right = new node;
            leaf->right->key_val = key;
            leaf->right->left = NULL;
            leaf->right->right = NULL;
        }
    }
}

/*
Function Name: maxKey
Description:
    Private BTREE function to find the maximum key
    value in the binary tree.
    
    Keep looking for right child nodes until the right
    child is NULL. Then return the current node's
    key value.
Input(s):
    leaf - node pointer. current btree node.
Return(s):
    max - integer. maximum key value in tree.
*/
int btree::maxKey(node *leaf) {
    if (leaf->right != NULL) return maxKey(leaf->right);
    else return leaf->key_val;
}

/*
Function Name: minKey
Description:
    Private BTREE function to find the minimum key
    value in the binary tree.
    
    Keep looking for left child nodes until the left
    child is NULL. Then return the current node's
    key value.
Input(s):
    leaf - node pointer. current btree node.
Return(s):
    min - integer. minimum key value in tree.
*/
int btree::minKey(node *leaf) {
    if (leaf->left != NULL) return minKey(leaf->left);
    else return leaf->key_val;
}

/*
Function Name: search
Description:
    Private BTREE function to search for a key value in the
    binary tree and return the node with that value.
Input(s):
    key - integer. value to look for in tree.
    leaf - node pointer. current node in search.
Return(s):
    leaf - node pointer. leaf with value.
    NULL - value not found in tree.
*/
node *btree::search(int key, node *leaf) {
    if (leaf != NULL) {
        if (leaf->key_val == key) return leaf;
        else if (key < leaf->key_val) return search(key, leaf->left);
        else return search(key, leaf->right);
    } else {
        return NULL;
    }
}

// --------- PUBLIC Class Functions --------------

/*
Function Name: destroy_tree
Description:
    Public BTREE function to destroy the binary tree.
Input(s):
    None
Return(s):
    None
*/
void btree::destroy_tree() {
    destroy_tree(root);
}

/*
Function Name: display_tree
Description:
    Public function designed to display the binary tree.
    
    This part checks if the root node is NULL. If the root
    is not NULL, it calls the private function display_tree
    and gives the root node as the leaf, otherwise it prints
    a message telling the user that the tree is empty.
Input(s):
    None
Return(s):
    None
*/
void btree::display_tree() {
    if (root != NULL) display_tree(root);
    else std::cout << "Tree Is Empty. Nothing To Display" << std::endl;
}

/*
Function Name: display_tree_rev
Description:
    Public function designed to display the binary tree.
    
    This part checks if the root node is NULL. If the root
    is not NULL, it calls the private function display_tree_rev
    and gives the root node as the leaf, otherwise it prints
    a message telling the user that the tree is empty.
Input(s):
    None
Return(s):
    None
*/
void btree::display_tree_rev() {
    if (root != NULL) display_tree_rev(root);
    else std::cout << "Tree Is Empty. Nothing To Display" << std::endl;
}

/*
Function Name: insert
Description:    
    Public BTREE function to insert key value
    into binary tree.
Input(s):
    key - integer value to insert.
Return(s):
    None
*/
void btree::insert(int key) {
    if (root != NULL) {
        insert(key,root);
    } else {
        root = new node;
        root->key_val = key;
        root->left = NULL;
        root->right = NULL;
    }
}

/*
Function Name: maxKey
Description:
    Public BTREE function to find the maximum key
    value in the binary tree.
Input(s):
    None
Return(s):
    max - integer. maximum key value in tree.
*/
int btree::maxKey() {
    if (root != NULL) {
        return maxKey(root);
    } else {
        return std::numeric_limits<int>::max();
    }
}

/*
Function Name: minKey
Description:
    Public BTREE function to find the minimum key
    value in the binary tree.
Input(s):
    None
Return(s):
    min - integer. minimum key value in tree.
*/
int btree::minKey() {
    if (root != NULL) {
        return minKey(root);
    } else {
        return std::numeric_limits<int>::min();
    }
}

/*
Function Name: search
Description:
    Public BTREE function to search for a key value in the
    binary tree and return the node with that value.
Input(s):
    key - integer. value to look for in tree.
Return(s):
    leaf - node pointer. leaf with value.
    NULL - value not found in tree.
*/
node *btree::search(int key) {
    return search(key, root);
}
// --------- END Class Functions --------------

/*
    Main Function
*/
int main(void) {
    // ------ Create New Binary Tree ------
    btree *my_tree = new btree;
    
    // ------ Populate Binary Tree --------
    my_tree->insert(90);
    my_tree->insert(100);
    my_tree->insert(23);
    my_tree->insert(20);
    my_tree->insert(120);
    my_tree->insert(10);
    my_tree->insert(14);
    
    // ------ Search Tree For Value ------
    node *loc = NULL;
    loc = my_tree->search(23);
    
    printChar();
    
    if (loc != NULL) std::cout << "Value 23 FOUND In Tree!" << std::endl;
    else std::cout << "Value 23 NOT FOUND In Tree" << std::endl;
    
    // ------ Print Min & Max Tree Values ------
    printChar();
    
    std::cout << "Minimum key value: " << my_tree->minKey() << std::endl;
    std::cout << "Maximum key value: " << my_tree->maxKey() << std::endl;

    // ------ Print Out BTREE ------    
    printChar();
    std::cout << "Low to High: " << std::endl;
    my_tree->display_tree();
    printChar('*',15);
    std::cout << "High to Low: " << std::endl;
    my_tree->display_tree_rev();

    // ------ Delete BTREE & Exit ------    
    printChar();
    delete my_tree;
    
    return 0;
}

/*
    Sub Functions
*/

/*
Function Name: printChar
Description:
    Function to print a certain character a number of times
    on a line.
Input(s):
    c - char. character to print. defaults to '-'
    n - int. number of times to print the character. defaults to 40
Return(s):  
    None
*/
void printChar(char c, int n) {
    for (int i = 0; i < n; i++) std::cout << c;
    std::cout << std::endl;
}
