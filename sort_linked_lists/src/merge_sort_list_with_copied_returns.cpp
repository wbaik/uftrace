#include <iostream>
#include <list>
using namespace std;
std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}

list<int> mergeTwoSortedList(list<int>& l, list<int>& r) {
    list<int> ret;
    while (!l.empty() && !r.empty()) {

        if (l.front() <= r.front()) {
            ret.push_back(l.front());
            l.pop_front();
        } else {
            ret.push_back(r.front());
            r.pop_front();
        }
    }
    auto& toPop = l.empty() ? r: l;
    while (!toPop.empty()) {
        ret.push_back(toPop.front());
        toPop.pop_front();
    }
    return ret;
}

list<int> merge_sort_list(list<int> & list1) {

    if (list1.size() <= 1) {
        return list1;
    }
    std::list<int> list2;

    auto it = list1.begin();
    std::advance(it, list1.size()/2);

    list2.splice(list2.begin(), list1, it, list1.end());

    auto left = merge_sort_list(list1);
    auto right = merge_sort_list(list2);
    return mergeTwoSortedList(left, right);
    // return mergeTwoSortedList(merge_sort_list(list1),merge_sort_list(list2));
    //                           ˆˆˆ This is an error!
    //                           mergeTwoSorted takes references!

}

int main ()
{
    std::list<int> someList;
    for (int i = 0; i < 10000; ++i) {
        someList.push_back(std::rand()%9997);
    }
    auto ret = merge_sort_list(someList);
    cout << ret << endl;

    return 0;

}
