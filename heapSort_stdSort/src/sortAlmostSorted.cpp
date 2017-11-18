#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include <queue>
#include <cassert>
using namespace std; // for the time being

// Suppose each element of the array is at most "k" places away 
// from the correct placement. Sort it to be correct

using vec = vector<int>;

void heap_sort(vec& given, int k, vec& ret) {
    auto cmp = [](const auto& l, const auto& r) {
        return l >= r;
    };
    std::priority_queue<int, vec, decltype(cmp)> myQueue(cmp);

    for(int i = 0; i < k; ++i) {
        myQueue.push(given[i]);
    }

    while (!myQueue.empty()) {
        ret.push_back(myQueue.top());
        myQueue.pop();
        if (k == given.size()) {
            break;
        }
        myQueue.push(given[k++]);
    }
    while(!myQueue.empty()) {
        ret.push_back(myQueue.top());
        myQueue.pop();
    }
}


int main() {

    int maxArraySize = 10000;
    vec given;
    for (int i = 0; i < maxArraySize; ++i) {
        given.push_back(std::rand());
    }
    // compare against a case where given is allocated with 
    // predefined size and each element is set by assignment
    // instaed of ::push_back() function
    // vec given(maxArraySize,0);
    // for (int i = 0; i < maxArraySize; ++i) {
    //     given[i] = std::rand();
    // }
    vec ret;
    heap_sort(given, maxArraySize, ret);
    sort(given.begin(), given.end());
    
    assert(equal(ret.begin(), ret.end(), given.begin(), given.end()));

    return 0;
}
