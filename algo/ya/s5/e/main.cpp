#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;
  Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
};  
#endif

#ifdef REMOTE_JUDGE
#include "solution_tree.h"
#endif
#include <cmath>
#include <iostream>
#include <cassert>
#include <optional>

using namespace std;

bool solution(const Node* root, std::optional<int> from , std::optional<int> to ) {
    if (root == nullptr) {
        return true;
    }

    if (from.has_value() && root->value <= from.value()) {
        return false;
    }

    if (to.has_value() && root->value >= to.value()) {
        return false; 
    }

    return solution(root->left, from, root->value) && solution(root->right, root->value, to);
}

bool Solution(const Node* root) {
    return solution(root, std::nullopt, std::nullopt);
} 

#ifndef REMOTE_JUDGE
void test() {
    {
      Node node1({1, nullptr, nullptr});
      Node node2({4, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(Solution(&node5));
    }
    {
      Node node1({1, nullptr, nullptr});
      Node node2({5, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(!Solution(&node5));
    }
}


int main() {
  test();
}
#endif