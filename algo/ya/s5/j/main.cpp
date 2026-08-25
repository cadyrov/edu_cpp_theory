#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  Node* left = nullptr;  
  Node* right = nullptr;
  Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
};  
#endif

#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cmath>
#include <iostream>
#include <cassert>

Node* insert(Node* root, int key) {
    if (root == nullptr) {
        Node node1(key, nullptr, nullptr);
        return &node1;
    }

    if (root->value <= key) {
        if  (root->right == nullptr) {
            Node node1(key, nullptr, nullptr);
            root->right = new Node(node1);
            
            return root;
        } else {
            root->right = insert(root->right, key);
        }

        return root;
    }
    
    if  (root->left == nullptr) {
        Node node1(key, nullptr, nullptr);
        root->left = new Node(node1);
            
        return root;
    } else {
        root->left = insert(root->left, key);
    }

    return root;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1(7, nullptr, nullptr);
    Node node2(8, &node1, nullptr);
    Node node3(7, nullptr, &node2);
    Node* newHead = insert(&node3, 6);
    assert(newHead->left->value == 6);
    assert(newHead == &node3);
}

int main() {
  test();
}
#endif