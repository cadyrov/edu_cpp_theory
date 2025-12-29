#include <vector>
#include <iostream>

using namespace std;

// Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.

class Solution {
    public:
        vector<int> sortedSquares(vector<int>& nums) {
            int l = 0;
            int r = nums.size()-1;
            int pos = nums.size()-1;
            vector<int> dst(nums.size());

            for (;l < r;) {
                if (abs(nums[l]) > abs(nums[r])) {
                    dst[pos] = nums[l]*nums[l];

                    l++;
                } else {
                    dst[pos] = nums[r]*nums[r];
                
                    r--;
                }
                
                pos--;
            }

            return dst;
        }
    };


    int main() {
        vector<int> data = {-5,-3,-2,-1};

        Solution{}.sortedSquares(data);

        for (auto it = data.begin(); it != data.end(); ++it  ) {
            cout << *it << " ";
        }

        cout << endl;

        data = {-7,-3,2,3,11};

        Solution{}.sortedSquares(data);

        for (auto it = data.begin(); it != data.end(); ++it  ) {
            cout << *it << " ";
        }

        cout << endl;

       return 0; 
    }