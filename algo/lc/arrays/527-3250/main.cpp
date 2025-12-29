#include <algorithm>
#include <vector>
#include <cassert>

//Given an array arr of integers, check if there exist two indices i and j such that :
// i != j
// 0 <= i, j < arr.length
// arr[i] == 2 * arr[j]
class Solution {
public:
    bool checkIfExist(std::vector<int>& arr) {
        std::sort(arr.begin(), arr.end());
        
        for (int i =0; i < arr.size(); ++i) {
            int idx = findBinary(arr,  arr[i]*2);

            if (idx >= 0 && idx != i) {
                return true;
            }
        }

        return false;
    }

    int findBinary(const std::vector<int>& arr, int target) const{
        int l = 0;
        int r = arr.size()-1;

        for (;l <=r;) {
            int mid = l + (r-l)/2;

            if (arr[mid] == target) {
                return mid;
            }

            if (arr[mid]<target) {
                l = mid+1;
            } else {
                r = mid -1;
            }
        }

        return -1;
    }
};

int main() {
    std::vector<int> data  ={1,2,3,4,5,6,7, 8};
    assert(Solution().checkIfExist(data));
    data  ={1,3,4,11};
    assert(!Solution().checkIfExist(data));
    
    return 0;
}