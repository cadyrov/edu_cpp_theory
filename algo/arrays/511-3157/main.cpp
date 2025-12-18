# include <vector>
# include <iostream>



// Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.
// Note that you must do this in-place without making a copy of the array.
// Input: nums = [0,1,0,3,12]
// Output: [1,3,12,0,0]

class Solution {
public:
    void moveZeroes(std::vector<int>& nums) {
        if (nums.size() < 2) {
            return;
        }

        int l = 0;
        int r = 1;


        for (;r < nums.size();) {
            if (nums[l] != 0) {
                ++l;
                ++r;

                continue;
            }

            if (nums[r]!= 0) {
                nums[l]= nums[r];
                nums[r]= 0;
                ++l;
                ++r;

                continue;
            }

            ++r;
        }
    }
};


int main() {
    std::vector<int> data{0,1,0,3,12};
    Solution sc;

    sc.moveZeroes(data);

    for (auto it =data.begin(); it != data.end(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    return 0;
}