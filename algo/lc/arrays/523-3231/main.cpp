#include <algorithm>
#include <vector>
#include <iostream>
#include <optional>

// Given an integer array nums, return the third distinct maximum number in this array. 
// If the third maximum does not exist, return the maximum number.
// Input: nums = [1,2]
// Output: 2
// Explanation:
// The first distinct maximum is 2.
// The second distinct maximum is 1.
// The third distinct maximum does not exist, so the maximum (2) is returned instead.
using namespace std;

class Solution {
    optional<int> a;
    optional<int> b;
    optional<int> c;
public:
    int thirdMax(vector<int>& nums) {
        for (auto it = nums.begin(); it != nums.end() ;++it) {
            set(b, c, set(a, b, *it));
            print("after");
        }
        
        if (c.has_value()) {
            return *c;
        }

        if (a.has_value()) {
            return *a;
        }

        if (b.has_value()) {
            return *b;
        }

        return 0;
    }


    optional<int> set(optional<int>& a, optional<int>& b , optional<int> in) {
        if (!in.has_value()) {
            return nullopt;
        }

        if (!a.has_value() || *a == *in) {
            a = *in;

            return nullopt;
        }

        if (!b.has_value() || *b == *in) {
            b = *in;

            if (b > a) {
                std::swap(a, b);
            }

            return nullopt;
        }

        if(*a < *in) {
           std::swap(a, in);
        }

        if(*b < *in) {
            std::swap(b, in); 
        }
        
        return in;
    }

    void print(const std::string& in) {
        std:cout << in << " ";
       
        std::cout << "a: ";
        a.has_value() ?  std::cout << *a :  std::cout << "null";
        std::cout << "; ";
        std::cout << "b: ";
        b.has_value() ?  std::cout << *b :  std::cout << "null";
        std::cout << "; ";
        std::cout << "c: ";
        c.has_value() ?  std::cout << *c :  std::cout << "null";
        std::cout << "; ";

        std::cout << std::endl;
    }

};



int main() {
    std::vector<int> data{3,1,2,2};

    Solution sc;

    cout << sc.thirdMax(data) << endl;


    sc = Solution();
    data={5,2,2};
    cout << sc.thirdMax(data) << endl;

    sc = Solution();
    data={1,2};
    cout << sc.thirdMax(data) << endl;

    return 0;
}