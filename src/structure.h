#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <iostream>
//
//Queue structure
//
template <class U>
class queue {
    private:
        struct node {
            U data;
            node* next;
            node(U d) : data(d), next(nullptr) {}
        };
        node* head;
    public:
        queue() : head(new node(U())) {}
        ~queue();
        void enqueue(U data);
        bool is_empty();
        U dequeue();
};

template <class U>
queue<U>::~queue() {
    try {
        while (this->head->next) this->dequeue();
    } catch (const std::domain_error& msg) {}
    delete this->head;
}

template <class U>
void queue<U>::enqueue(U data) {
    node* curr = this->head;
    while (curr->next) curr = curr->next;
    curr->next = new node(data);
}

template <class U>
U queue<U>::dequeue() {
    if (this->head->next) {
        node* to_delete = this->head->next;
        this->head->next = to_delete->next;
        U value = to_delete->data;
        delete to_delete;
        return value;
    } else throw std::domain_error("Out of bounds.");
}

template <class U>
bool queue<U>::is_empty() {
    if (this->head->next) return false;
    else return true;
}
//
//Tree structure and members
//
template <class T>
class tree {
    private:
        struct tree_node {
            T data;
            tree_node* right;
            tree_node* left;
            int height;
            tree_node() : right(nullptr), left(nullptr), height(1) {}
            tree_node(T d) : data(d), right(nullptr), left(nullptr), height(1) {}
        };
        unsigned int size;
        tree_node* head;
    protected:
        tree_node* recurr_insert(T data, tree_node* curr);
        void recurr_print(queue<tree_node*>* q);
        tree_node* right_rotate(tree_node* root);
        tree_node* left_rotate(tree_node* root);
    public:
        tree() : head(nullptr), size(0) {}
        ~tree(); //we can perform some depthfirst post order traversel to clear nodes.
        void insert(T data);
        void print();
};

//INCOMPLETE
template <class T>
tree<T>::~tree() {
    
}

template <class T>
void tree<T>::insert(T data) {
    this->head = recurr_insert(data, head);
}

template <class T>
typename tree<T>::tree_node* tree<T>::recurr_insert(T data, tree_node* curr) {
    if (!curr) {
        return new tree_node(data);
    } else {
        //insert
        if (data > curr->data) {
            curr->right = this->recurr_insert(data, curr->right);
        } else {
            curr->left = this->recurr_insert(data, curr->left);         
        }
        //update height
        int right_height = curr->right ? curr->right->height : 0;
        int left_height = curr->left ? curr->left->height : 0;
        curr->height = right_height > left_height ? right_height + 1 : left_height + 1;
        //balacne
        int balance = right_height - left_height;
        if (balance > 1 && data > curr->right->data) curr = this->left_rotate(curr); //ror
        else if (balance < -1 && data <= curr->left->data) curr = this->right_rotate(curr);//lol
        else if (balance > 1 && data <= curr->right->data) { //rol
            curr->right = this->right_rotate(curr->right);
            curr = this->left_rotate(curr);
        } else if (balance < -1 && data > curr->left->data) { //lor
            curr->left = this->left_rotate(curr->left);
            curr = this->right_rotate(curr);
        }
        return curr;
    }
}

template <class T>
typename tree<T>::tree_node* tree<T>::right_rotate(tree_node* root) {
    //initialize
    tree_node* left = root->left;
    //swap
    root->left = left->right;
    left->right = root;
    //adjust height
    int rl_height = root->left ? root->left->height : 0;
    int rr_height = root->right ? root->right->height : 0;
    root->height = rl_height > rr_height ? rl_height + 1 : rr_height + 1;
    left->height = left->left && left->right->height <= left->left->height ? 
        left->left->height + 1 : left->right->height + 1;

    return left;
}

template <class T>
typename tree<T>::tree_node* tree<T>::left_rotate(tree_node* root) {
    //initialize
    tree_node* right = root->right;
    //swap pointers
    root->right = right->left;
    right->left = root;
    //adjust height;
    int rl_height = root->left ? root->left->height : 0;
    int rr_height = root->right ? root->right->height : 0;
    root->height = rl_height > rr_height ? rl_height + 1 : rr_height + 1;
    right->height = right->right && right->right->height > right->left->height ? 
        right->right->height + 1 : right->left->height + 1;

    return right;
}

template <class T>
void tree<T>::print() {
    queue<tree_node*>* q = new queue<tree_node*>();
    if (this->head) {
        q->enqueue(this->head);
        recurr_print(q);
    }
    delete q;
}

template <class T>
void tree<T>::recurr_print(queue<tree<T>::tree_node*> *q) {
    if (q->is_empty()) return;
    else {
        tree_node* curr = q->dequeue();
        if (curr->left) q->enqueue(curr->left);
        if (curr->right) q->enqueue(curr->right);
        std::cout << curr->data << std::endl;
        this->recurr_print(q);
    }
}


#endif