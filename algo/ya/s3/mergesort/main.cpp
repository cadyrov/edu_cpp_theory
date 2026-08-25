#include <vector>
#include <cassert>

using Iterator = std::vector<int>::iterator;
using CIterator = std::vector<int>::const_iterator;

std::vector<int> merge(
	CIterator left_begin, CIterator left_end, 
	CIterator right_begin, CIterator right_end) {	
    std::vector<int> result{};

    result.reserve(std::distance(left_begin, left_end) + std::distance(right_begin, right_end));
    
    for (;;) {
        if (left_begin == left_end) {
            result.insert(result.end(), right_begin, right_end);
            break;
        }
        
        if (right_begin == right_end) {
            result.insert(result.end(), left_begin, left_end);
            break;
        }
        
        if (*left_begin < *right_begin) {
            result.push_back(*left_begin);
            ++left_begin;
        } else {
            result.push_back(*right_begin);
            ++right_begin;
        }
    }

    return result;
}

void merge_sort(Iterator begin, Iterator end) {
	auto distance = std::distance(begin, end);
	if (distance <= 1) {
		return;
	}

    auto middle = begin + distance / 2;

    merge_sort(begin, middle);
    merge_sort(middle, end);

    std::vector<int> sorted = merge(begin, middle, middle, end);
    std::move(sorted.begin(), sorted.end(), begin);
}

void test_merge_sort() {
	std::vector<int> a = {1, 4, 9};
	std::vector<int> b = {2, 10, 11};
	std::vector<int> c = merge(a.cbegin(), a.cend(), b.cbegin(), b.cend());
	std::vector<int> expected = {1, 2, 4, 9, 10, 11};
	assert(c == expected);
	std::vector<int> d = {1, 4, 2, 10, 1, 2};
	std::vector<int> sorted = {1, 1, 2, 2, 4, 10};
	merge_sort(d.begin(), d.end());
	assert(d == sorted);
}