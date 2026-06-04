#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  Node* left = nullptr;  
  Node* right = nullptr;
  Node(Node* left, Node* right, int value) : value(value), left(left), right(right) {}
};  
#endif
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cassert>


Node* remove(Node* root, int key) {
    Node* parent = nullptr;
    Node* current = root;

    while (current && current->value != key) {
        parent = current;
        current = (key < current->value) ? current->left : current->right;
    }

    if (!current) {
        return root;
    }

    auto replaceChild = [&root](Node* parent, Node* oldChild, Node* newChild) {
        if (!parent) {
            root = newChild;
        } else if (parent->left == oldChild) {
            parent->left = newChild;
        } else {
            parent->right = newChild;
        }
    };

    if (!current->left) {
        replaceChild(parent, current, current->right);
    } else if (!current->right) {
        replaceChild(parent, current, current->left);
    } else {
        Node* successorParent = current;
        Node* successor = current->right;

        while (successor->left) {
            successorParent = successor;
            successor = successor->left;
        }

        if (successorParent != current) {
            successorParent->left = successor->right;
            successor->right = current->right;
        }

        successor->left = current->left;
        replaceChild(parent, current, successor);
    }

    return root;
}


#ifndef REMOTE_JUDGE
void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);
}

int main() {
  test();
}
#endif