#include <vector>
#include <iostream>


// Given an array arr, replace every element in that array with the greatest element among the elements to its right, 
// and replace the last element with -1.
class Solution {
    public:
        std::vector<int> replaceElements(std::vector<int>& arr) {
            for (int i =0; i < arr.size(); ++i) {
                int idx = greatestRight(arr, i);

                if (idx == -1) {
                    arr[i]=-1;
                } else {
                    for (;i < idx;) {
                        arr[i] = arr[idx];
                        ++i;
                    }
                    i = idx-1;
                }
            }
            
            return arr;
        }
        
        int greatestRight(const std::vector<int>& arr, int l) const {
            if (l == arr.size()-1) {
                return -1;
            }
            
            int max = l+1;
            
            for (int i=max;i < arr.size();++i) {
                if (arr[i] >= arr[max]) {
                    max = i;
                }
            }
            
            return max;
        }
    };

    int main() {
        Solution s{};

        std::vector<int> data{17,18,5,4,6,1}; // => [18,6,6,6,1,-1]

        s.replaceElements(data);

        for (auto it = data.begin(); it != data.end(); it++) {
            std::cout << *it << " ";
        }

        std::cout << std::endl;
    }