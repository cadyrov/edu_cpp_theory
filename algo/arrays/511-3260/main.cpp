#include <algorithm>
#include <vector>
#include <iostream>

// Given an integer array nums, move all the even integers at the beginning of the array followed by all the odd integers.
// Return any array that satisfies this condition.
// [3,1,2,4] => [4,2,3,1]|| [2,4,1,3]|| [4,2,1,3]
using namespace std;

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums;
        }

        int l = 0;
        int r = 1;
        
        for (;r < nums.size();) {
            if (nums[l]%2 == 0) {
                ++l;
                ++r;

                continue;
            }

            if (nums[r]%2 == 0) {
                swap(nums[r], nums[l]);

                continue;
            }

            ++r;
        }
        
        return nums;  
    }
};



int main() {
    std::vector<int> data{3,1,2,4};

    Solution sc;

    sc.sortArrayByParity(data);

    for (auto it = data.begin();it != data.end();++it) {
        cout << *it << " ";   
    }

    cout << endl;

    return 0;
}