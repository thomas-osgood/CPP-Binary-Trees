/*
Created By: Thomas Osgood
*/
#include <iomanip>
#include <iostream>

struct node {
    unsigned int year;
    unsigned int job_number;
    float job_cost;
    float job_estimate;
    node* left;
    node* right;
};

class btree {

public:
    btree();
    ~btree();
    void delete_job(unsigned int year, unsigned int jno);
    void destroy_tree();
    void new_job(unsigned int year, unsigned int job_number, float job_cost = 0.0, float job_estimate = 0.0);
    void print_ascending();
    void print_descending();
    node* search_job(unsigned int year, unsigned int jno);
    node* search_newest();
    node* search_oldest();
    
private:
    node* delete_job(node *leaf, unsigned int year, unsigned int jno);
    void destroy_tree(node *leaf);
    void new_job(node* leaf, unsigned int year, unsigned int job_number, float job_cost, float job_estimate);
    void print_ascending(node *leaf);
    void printChar(char c = '-', int n = 40);
    void print_descending(node *leaf);
    node* search_job(node* leaf, unsigned int year, unsigned int jno);
    node* search_newest(node *leaf);
    node* search_oldest(node *leaf);
    
    node* root;
};

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
    std::cout << "[+] Initializing Binary Tree ..." << std::endl;
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
    std::cout << "[-] Destroying Binary Tree ..." << std::endl;
    destroy_tree();
}

// --------- PRIVATE Class Functions --------------

/*
Function Name: delete_job
Description:
    Private BTREE function to delete a job node.
Input(s):
    leaf - node pointer. node to delete.
    year - unsigned int. job year.
    jno - unsigned int. job number.
Return(s):
    leaf - node pointer. new link for tree.
    NULL - nothing. end of tree.
*/
node* btree::delete_job(node* leaf, unsigned int year, unsigned int jno) {
    if (leaf == NULL) return NULL;
    else if (year < leaf->year) leaf->left = delete_job(leaf->left,year,jno);
    else if (year > leaf->year) leaf->right = delete_job(leaf->right,year,jno);
    else {
        if (jno < leaf->job_number) leaf->left = delete_job(leaf->left,year,jno);
        else if (jno > leaf->job_number) leaf->right = delete_job(leaf->right,year,jno);
        else {
            if ((leaf->left == NULL) && (leaf->right == NULL)) {
                delete leaf;
                return NULL;
            } else if (leaf->left == NULL) {
                node* temp = NULL;
                temp = leaf->right;
                delete leaf;
                return temp;
            } else if (leaf->right == NULL) {
                node* temp = NULL;
                temp = leaf->left;
                delete leaf;
                return temp;
            } else { // two children
                node* temp = NULL;
                temp = search_oldest(leaf->right);
                leaf->year = temp->year;
                leaf->job_number = temp->job_number;
                leaf->job_cost = temp->job_cost;
                leaf->job_estimate = temp->job_estimate;
                leaf->right = delete_job(leaf->right,temp->year,temp->job_number);
            }
        }
    }
    return leaf;
}

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
Function Name: new_job
Description:    
    Private BTREE function to insert new job
    into binary tree.
    
    First compares job year, then compares job number.
Input(s):
    leaf - node pointer. current node/leaf.
    year - unsigned integer. job year.
    job_number - unsigned integer. job number.
    job_cost - float. actual cost of job.
    job_estimate - float. estimated cost of job.
Return(s):
    None
*/
void btree::new_job(node* leaf, unsigned int year, unsigned int job_number, float job_cost, float job_estimate) {
    if (year < leaf->year) {
        if (leaf->left != NULL)
            new_job(leaf->left,year,job_number,job_cost,job_estimate);
        else {
            leaf->left = new node;
            leaf->left->year = year;
            leaf->left->job_number = job_number;
            leaf->left->job_cost = job_cost;
            leaf->left->job_estimate = job_estimate;
            leaf->left->left = NULL;
            leaf->left->right = NULL;
        }
    } else if (year > leaf->year) {
        if (leaf->right != NULL)
            new_job(leaf->right,year,job_number,job_cost,job_estimate);
        else {
            leaf->right = new node;
            leaf->right->year = year;
            leaf->right->job_number = job_number;
            leaf->right->job_cost = job_cost;
            leaf->right->job_estimate = job_estimate;
            leaf->right->left = NULL;
            leaf->right->right = NULL;
        }
    } else {
        if (job_number < leaf->job_number) {
            if (leaf->left != NULL)
                new_job(leaf->left,year,job_number,job_cost,job_estimate);
            else {
                leaf->left = new node;
                leaf->left->year = year;
                leaf->left->job_number = job_number;
                leaf->left->job_cost = job_cost;
                leaf->left->job_estimate = job_estimate;
                leaf->left->left = NULL;
                leaf->left->right = NULL;
            }
        } else if (job_number > leaf->job_number) {
            if (leaf->right != NULL)
                new_job(leaf->right,year,job_number,job_cost,job_estimate);
            else {
                leaf->right = new node;
                leaf->right->year = year;
                leaf->right->job_number = job_number;
                leaf->right->job_cost = job_cost;
                leaf->right->job_estimate = job_estimate;
                leaf->right->left = NULL;
                leaf->right->right = NULL;
            }
        } else {
            std::cout << "\033[33m[!] JOB " << year << "-" << job_number << " Already Exists.\033[0m" << std::endl;
            return;
        }
    }
}

/*
Function Name: print_ascending
Description:
    Private function designed to display the binary tree.
    
    Displays the tree in a left to right (ascending)
    order, checking for left nodes first, then displaying
    the current node, then checking for right nodes.
Input(s):
    leaf - node pointer. current leaf/node to display.
Return(s):
    None
*/
void btree::print_ascending(node *leaf) {
    if (leaf->left != NULL) print_ascending(leaf->left);
    std::locale loc(""); // Set LOCALE For $$ Formatting
    std::cout.imbue(loc); // Set COUT To Format Longer #s Like $$
    std::cout << "JOB: ";
    std::cout << std::setfill('0') << std::setw(2) << leaf->year << "-";
    std::cout << std::setfill('0') << std::setw(3) << leaf->job_number << std::endl;
    printChar('-',14);
    std::cout << "\tEstimate: " << leaf->job_estimate << std::endl;
    std::cout << "\tCost: " << leaf->job_cost << std::endl;
    std::cout << "\tProfit/Loss: " << (leaf->job_estimate - leaf->job_cost) << std::endl;
    printChar();
    if (leaf->right != NULL) print_ascending(leaf->right);
}

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
void btree::printChar(char c, int n) {
    for (int i = 0; i < n; i++) std::cout << c;
    std::cout << std::endl;
}

/*
Function Name: print_descending
Description:
    Private function designed to display the binary tree.
    
    Displays the tree in a right to left (descending)
    order, checking for left nodes first, then displaying
    the current node, then checking for right nodes.
Input(s):
    leaf - node pointer. current leaf/node to display.
Return(s):
    None
*/
void btree::print_descending(node *leaf) {
    if (leaf->right != NULL) print_ascending(leaf->right);
    std::locale loc(""); // Set LOCALE For $$ Formatting
    std::cout.imbue(loc); // Set COUT To Format Longer #s Like $$
    std::cout << "JOB: ";
    std::cout << std::setfill('0') << std::setw(2) << leaf->year << "-";
    std::cout << std::setfill('0') << std::setw(3) << leaf->job_number << std::endl;
    printChar('-',14);
    std::cout << "\tEstimate: " << leaf->job_estimate << std::endl;
    std::cout << "\tCost: " << leaf->job_cost << std::endl;
    std::cout << "\tProfit/Loss: " << (leaf->job_estimate - leaf->job_cost) << std::endl;
    printChar();
    if (leaf->left != NULL) print_ascending(leaf->left);
}

/*
Function Name: search_job
Description:
    Searches the tree for a job and returns the node if it exists.
    If the job does not exist, it returns NULL.
Input(s):
    leaf - node pointer. current node.
    year - unsigned integer. job year.
    jno - unsigned integer. job number. 
Return(s):
    leaf - node pointer. job node.
    NULL - job does not exist in tree.
*/
node* btree::search_job(node* leaf, unsigned int year, unsigned int jno) {
    if (leaf != NULL) {
        if ((leaf->year == year) && (leaf->job_number == jno)) return leaf;
        else if (year < leaf->year) return search_job(leaf->left, year, jno);
        else if (year > leaf->year) return search_job(leaf->right, year, jno);
        else if (jno < leaf->job_number) return search_job(leaf->left, year, jno);
        else return search_job(leaf->right, year, jno);
    } else {
        return NULL;
    }
}

/*
Function Name: search_newest
Description:
    Private BTREE function to find the newest job
    in the binary tree.
    
    Keep looking for right child nodes until the right
    child is NULL. Then return the current node.
    
    Newest is by most recent (year & job num).
Input(s):
    leaf - node pointer. current btree node.
Return(s):
    leaf - node pointer. newest (year & job num) job node.
*/
node* btree::search_newest(node *leaf) {
    if (leaf->right != NULL) return search_newest(leaf->right);
    else return leaf;
}

/*
Function Name: search_oldest
Description:
    Private BTREE function to find the oldest job
    in the binary tree.
    
    Keep looking for left child nodes until the left
    child is NULL. Then return the current node.
Input(s):
    leaf - node pointer. current btree node.
Return(s):
    leaf - node pointer. newest (year & job num) job node.
*/
node* btree::search_oldest(node *leaf) {
    if (leaf->left != NULL) return search_oldest(leaf->left);
    else return leaf;
}

// --------- PUBLIC Class Functions --------------

/*
Function Name: delete_job
Description:
    Public BTREE function to delete a job node.
Input(s):
    year - unsigned int. job year.
    jno - unsigned int. job number.
Return(s):
    None
*/
void btree::delete_job(unsigned int year, unsigned int jno) {
    if (root == NULL) {
        std::cout << "[*] Tree Empty. Nothing To Delete." << std::endl;
        return;
    }
    
    if (search_job(year,jno) == NULL) {
        std::cout << "\033[31mJob: " << year << "-";
        std::cout << std::setfill('0') << std::setw(3) << jno;
        std::cout << " Not Found.\033[0m" << std::endl;
        return;
    }
    delete_job(root, year, jno);
    return;
}

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
Function Name: new_job
Description:    
    Public BTREE function to insert new job
    into binary tree.
Input(s):
    year - unsigned integer. job year.
    job_number - unsigned integer. job number.
    job_cost - float. actual cost of job.
    job_estimate - float. estimated cost of job.
Return(s):
    None
*/
void btree::new_job(unsigned int year, unsigned int job_number, float job_cost, float job_estimate) {
    if (root != NULL) {
        new_job(root,year,job_number,job_cost,job_estimate);
    } else {
        root = new node;
        root->left = NULL;
        root->right = NULL;
        root->year = year;
        root->job_number = job_number;
        root->job_cost = job_cost;
        root->job_estimate = job_estimate;
    }
}

/*
Function Name: print_ascending
Description:
    Public function designed to display the binary tree.
    
    Calls the private function if there is a root node.
Input(s):
    None
Return(s):
    None
*/
void btree::print_ascending() {
    if (root != NULL) print_ascending(root);
    else std::cout << "\033[31m[!] No Jobs To Display\033[0m" << std::endl;
}

/*
Function Name: print_descending
Description:
    Private function designed to display the binary tree.
    
    Calls the private function if there is a root node.
Input(s):
    None
Return(s):
    None
*/
void btree::print_descending() {
    if (root != NULL) print_descending(root);
    else std::cout << "\033[31m[!] No Jobs To Display\033[0m" << std::endl;
}

/*
Function Name: search_job
Description:
    Searches the tree for a job and returns the node if it exists.
    If the job does not exist, it returns NULL.
Input(s):
    year - unsigned integer. job year.
    jno - unsigned integer. job number. 
Return(s):
    leaf - node pointer. job node.
    NULL - job does not exist in tree.
*/
node* btree::search_job(unsigned int year, unsigned int jno) {
if (root != NULL) {
        return search_job(root, year, jno);
    } else {
        std::cout << "\033[31m[!] No Jobs To Search\033[0m" << std::endl;
        return NULL;
    }
}

/*
Function Name: search_newest
Description:
    Public BTREE function to find the newest job
    in the binary tree.
Input(s):
    None.
Return(s):
    leaf - node pointer. newest (year & job num) job node.
*/
node* btree::search_newest() {
    if (root != NULL) return search_newest(root);
    else {
        std::cout << "\033[31m[!] No Jobs To Search\033[0m" << std::endl;
        return NULL;
    }
}

/*
Function Name: search_oldest
Description:
    Public BTREE function to find the oldest job
    in the binary tree.
Input(s):
    None.
Return(s):
    leaf - node pointer. newest (year & job num) job node.
*/
node* btree::search_oldest() {
    if (root != NULL) return search_oldest(root);
    else {
        std::cout << "[!] No Jobs To Search" << std::endl;
        return NULL;
    }
}

// --------- END Class Functions --------------


/*
Function Name: main
Description:
    Gets called everytime the program is run.
Input(s):
    None
Return(s):
    return_code - integer. 0 represents successfull run.
*/
int main() {
    btree *my_jobs = new btree;
    node* oldest = NULL;
    node* newest = NULL;
    
    // ---------- POPULATE JOB TREE ----------
    my_jobs->new_job(12,001,15000,32000);
    my_jobs->new_job(10,005,25000,22000);
    my_jobs->new_job(10,003,300,800);    
    my_jobs->new_job(10,006,400,400);
    my_jobs->new_job(11,035,250000,262000);
    my_jobs->new_job(21,007,18000,22000);
    my_jobs->new_job(21,004,0,19000);
    my_jobs->new_job(21,002);
    
    // ---------- DISPLAY JOB TREE ----------
    my_jobs->print_ascending();
    
    // ---------- DISPLAY OLDEST JOB ----------
    oldest = my_jobs->search_oldest();
    if (oldest != NULL) {
        std::cout << "Oldest Job: " << oldest->year << "-";
        std::cout << std::setfill('0') << std::setw(3) << oldest->job_number;
        std::cout << std::endl;
    }
    
    // ---------- DISPLAY NEWEST JOB ----------
    newest = my_jobs->search_newest();
    if (oldest != NULL) {
        std::cout << "Newest Job: " << newest->year << "-";
        std::cout << std::setfill('0') << std::setw(3) << newest->job_number;
        std::cout << std::endl;
    }
    
    for (int i = 0; i < 40; i++) std::cout << "-";
    std::cout << std::endl;
    
    // ---------- DELETE JOB ----------
    my_jobs->delete_job(10,005);
    my_jobs->delete_job(21,004);
    my_jobs->delete_job(10,003);
    my_jobs->print_ascending();
    
    oldest = my_jobs->search_oldest();
    if (oldest != NULL) {
        std::cout << "Oldest Job: " << oldest->year << "-";
        std::cout << std::setfill('0') << std::setw(3) << oldest->job_number;
        std::cout << std::endl;
    }
    
    // ---------- DELETE JOB TREE & LOCAL NODES ----------
    delete oldest;
    delete newest;
    delete my_jobs;
    
    return 0;
}
