#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


// Given an integer array nums sorted in non-decreasing order, 
// remove the duplicates in-place such that each unique element appears only once. 
// The relative order of the elements should be kept the same.
// Consider the number of unique elements in nums to be k​​​​​​​​​​​​​​. After removing duplicates, return the number of unique elements k.
class Solution {
public:
    int RemoveDuplicates(std::vector<int>& nums) const {
        if (nums.size()<2) {
            return nums.size();
        }

        size_t k = nums.size();
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i-1]) {
                --k;
            }
        }

        size_t l = 1;
        size_t r = 1;

        for (; l < k; ++l) {
            if (nums[l] <= nums[l-1]) {
                for (;nums[r]<=nums[l-1]&&r < nums.size();++r) {}
                if (r == nums.size()) {
                    return  k;
                }

                nums[l] = nums[r];
            }
        }

        return static_cast<int>(k);
    }
};

int main() {
    auto data = std::vector<int>{1, 2, 2, 2, 3, 3, 5};
    assert(Solution().RemoveDuplicates(data) == 4);
    data = std::vector<int>{1};
    assert(Solution().RemoveDuplicates(data) == 1);
    data = std::vector<int>{1,1 };
    assert(Solution().RemoveDuplicates(data) == 1);

    std::cout << "tests accept, enter array" << std::endl;

    int n;
    std::vector<int> in;
    std::string line;
    
    std::getline(std::cin, line);
    std::stringstream ss(line);

    for (;ss >> n;) {
        in.push_back(n);
    } 

    assert(std::is_sorted(in.begin(), in.end()));
    
    int res = Solution().RemoveDuplicates(in);

    for (auto it = in.begin();it != in.end(); ++it) {
        std::cout << *it <<" ";
    }

    std::cout <<"\n"<< res << std::endl;

    return 0;
}

