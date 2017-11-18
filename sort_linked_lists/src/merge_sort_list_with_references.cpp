#include <list>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <queue>
#include <iostream>

using namespace std; // for the time being...

// implement merge_sort with std::list, use references and no return values

template <typename T>
void merge_two_sorted_list(std::list<T>& left, std::list<T>& right) {

    // should use auto, but to remind myself the need of `typename`
    typename std::list<T>::const_iterator left_iter = left.cbegin();
    typename std::list<T>::const_iterator right_iter = right.cbegin();

    while (left_iter != left.cend() && right_iter != right.cend()) {
        if (*left_iter < *right_iter) {
            std::advance(left_iter,1);
        } else {
            auto next_right_iter = std::next(right_iter);
            // When we splice this, right_iter gets transferred to left??? 
            left.splice(left_iter, right, right_iter);
            right_iter = next_right_iter;
        }
    }

    if (!right.empty()) {
        left.splice(left.end(), right, right_iter, right.end());
    }
}

template <typename T>
void merge_sort_list(std::list<T>& givenList) {
    if (givenList.size() <=1) {
        return;
    }
    // Use givenList as a left half once spliced
    // std::list::const_iterator is a must for list::splice()
    typename std::list<T>::const_iterator mid_point = givenList.begin();
    std::advance(mid_point, givenList.size()/2);

    std::list<T> rightHalf;
    rightHalf.splice(rightHalf.begin(), givenList, mid_point, givenList.end());

    merge_sort_list(givenList);
    merge_sort_list(rightHalf);

    merge_two_sorted_list(givenList, rightHalf);
}


int main() {

    list<int> someList;

    for (int i = 0; i < 10000; ++i) {
        someList.push_back(std::rand()%9997);
    }

    merge_sort_list(someList);
    for (const auto& i : someList) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
