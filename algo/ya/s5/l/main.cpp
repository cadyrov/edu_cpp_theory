    #include <vector>
    #include <cassert>
    #include <algorithm>
    #ifdef REMOTE_JUDGE
    #include "solution.h"
    #endif


    int siftDown(std::vector<int>& heap, int idx) {
        for (;;) {
            int left = idx * 2;
            int right = left + 1;
            int largest = idx;

            if (left < static_cast<int>(heap.size()) && heap[left] > heap[largest]) {
                largest = left;
            }

            if (right < static_cast<int>(heap.size()) && heap[right] > heap[largest]) {
                largest = right;
            }

            if (largest == idx) {
                return idx;
            }

            std::swap(heap[idx], heap[largest]);
            idx = largest;
        }
    }

    #ifndef REMOTE_JUDGE
    void test() {
        std::vector<int> sample = {-1, 12, 1, 8, 3, 4, 7};
        assert(siftDown(sample, 2) == 5);
    }


    int main() {
        test();
    }
    #endif