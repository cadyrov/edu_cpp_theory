#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.

class Solution {
    public:
        vector<int> findDisappearedNumbers(vector<int>& nums) {
            std::sort(nums.begin(), nums.end());
            int l = 0;
           
            vector<int> dst;

           for (int i = 1; i <= nums.size(); ++i) {
                for (;l < nums.size() && nums[l] < i; ++l){}

                if (l >= nums.size() || nums[l] != i) {
                    dst.push_back(i);
                }
           }

           return dst;
        }
    };


    int main() {
        vector<int> data = {4,3,2,7,8,2,3,1};

        auto dst = Solution{}.findDisappearedNumbers(data);

        for (auto it = dst.begin(); it != dst.end(); ++it  ) {
            cout << *it << " ";
        }

        cout << endl;

        data = {1,1};

        dst = Solution{}.findDisappearedNumbers(data);

        for (auto it = dst.begin(); it != dst.end(); ++it  ) {
            cout << *it << " ";
        }

        cout << endl;

       return 0; 
    }