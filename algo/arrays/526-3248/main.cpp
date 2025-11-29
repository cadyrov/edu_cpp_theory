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
    int RemoveDuplicates(std::vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
 
        int left = 1;
        int right = 1;

        if  (nums.size() == 2 && nums[left] == nums[left]-1) { 
            return 1;
        }

        int limit = 0;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i -1]) {
                ++limit;
            }
        }



        for (;left < nums.size()-limit; ) {
            if (nums[left] <= nums[left]-1) {
                for (;right < nums.size() && (nums[right] <= nums[left-1] || right <=left);) {
                    ++right;
                }

                if (right < nums.size()) {
                    return left;
                }

                nums[left] = nums[right];
            }

            ++left;
            ++right;
        }

        return left;
    }
};

int main() {
    auto data = std::vector<int>{1, 2, 2, 2, 3, 3, 5};
    std::cout << Solution().RemoveDuplicates(data) << std::endl;
    assert(Solution().RemoveDuplicates(data) == 4);
    

    int n;
    std::vector<int> in;
    std::string line;
    
    std::getline(std::cin, line);
    std::stringstream ss(line);

    for (;ss >> n;) {
        in.push_back(n);
    } 

    assert(std::is_sorted(in.begin(), in.end()));
    
    Solution().RemoveDuplicates(in);

    for (auto it = in.begin();it != in.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}

