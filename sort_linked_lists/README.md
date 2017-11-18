## `UFTRACE` on implementation of linked lists

Comparing `heap_sort` vs `std::sort` naturally led me to think about linked list performance, since different implementations would lead to different performances. Using `uftrace`, a custom version of `linked list` is compared to `std::list<T>`.

### Getting Started

`uftrace` can be found [here](https://github.com/namhyung/uftrace).
`g++` is used with option `-std=c++17 -pg` to enable `uftrace <commands> <options>`. `-std=c++17` requires updated gcc, naturally.

### Purpose

The purpose of this writing is to compare performances of `merge sort` on a `linked list`, and utilize much of `modern c++` features.

### Running the tests

While one can use Makefile, running the separate commands are better for this purpose.

Run the following commands to use uftrace:

* Using my implementation of `merge_sort`, which passes references only for performance
```
g++ -std=c++17 -pg -o merge_sort_list_with_references merge_sort_list_with_references.cpp 
uftrace record -D 5 merge_sort_list_with_references
uftrace report --avg-total -t 10us -N ^_ -N ^std::__
```

* Using my implementation of `merge_sort`, which returns copied values for a performance comparison
```
g++ -std=c++17 -pg -o merge_sort_list_with_copied_returns merge_sort_list_with_copied_returns.cpp 
uftrace record -D 5 merge_sort_list_with_copied_returns
uftrace report --avg-total -t 10us -N ^_ -N ^std::__
```

* Using a customized struct and not `std::list` that was implemented in [Elements of Programming Interview](http://elementsofprogramminginterviews.com/solutions/)
```
g++ -std=c++17 -pg -o merge_sort_custom_struct merge_sort_custom_struct.cpp 
uftrace record -D 5 merge_sort_custom_struct
uftrace report --avg-total -t 10us -N ^_ -N ^std::__
```

### Takeaway

* Significant differences between `std::list` and custom implementatio by pointers, especially `std::shared_ptr`. The following is a comparison in `std::list` vs `custom implementation` on `merge_sort`ing 10,000 `int` elements.

```
Using std::list<int>
   Avg total   Min total   Max total  Function
  ==========  ==========  ==========  ====================================
  898.228 ms  898.228 ms  898.228 ms  main
    2.350 ms   15.121 us   11.682 ms  std::_List_base::_M_clear
  650.856 us   10.034 us  821.376 ms  merge_sort_list
  303.407 us   11.738 us   11.683 ms  std::_List_base::~_List_base
  257.130 us   11.947 us   11.684 ms  std::list::~list
  142.413 us   12.327 us    1.690 ms  std::basic_ostream::operator <<
  111.309 us   10.016 us   52.301 ms  merge_two_sorted_list
   47.270 us   47.270 us   47.270 us  std::endl
   26.674 us   10.156 us    1.049 ms  std::advance
   20.836 us   11.189 us   78.072 us  std::allocator::allocator
   20.813 us   10.003 us  132.022 us  std::list::splice
   19.930 us   10.230 us   90.037 us  std::_List_base::_S_distance
   19.527 us   11.418 us   78.336 us  std::_List_base::_List_impl::_List_impl
   19.188 us   10.004 us   35.330 us  std::list::_M_insert
   19.118 us   10.003 us   65.680 us  std::list::push_back
   19.114 us   10.846 us  127.586 us  std::_List_const_iterator::_M_const_cast
   18.983 us   10.250 us   90.887 us  std::list::size
   18.936 us   12.208 us   79.259 us  std::list::list

Using custom implementation
  Total time   Self time       Calls  Function
  ==========  ==========  ==========  ====================================
   10.093  s    2.790  s           1  main
    6.494  s    3.750  s       90114  StableSortList
    2.382  s    2.144  s       56943  MergeTwoSortedLists
  476.475 ms   98.280 ms       10455  std::_Sp_counted_base::_M_release
  451.307 ms    6.477 ms        9321  std::shared_ptr::~shared_ptr
  427.728 ms    4.735 ms        8496  std::__shared_ptr::~__shared_ptr
  415.559 ms    3.180 ms        8087  std::__shared_count::~__shared_count
  294.049 ms   42.497 ms        9417  std::make_shared
  257.085 ms   15.831 ms        8545  std::shared_ptr::shared_ptr
  250.174 ms   12.145 ms        8250  std::allocate_shared
  231.231 ms   45.671 ms        7823  std::__shared_ptr::__shared_ptr
  141.979 ms   12.739 ms        5028  std::shared_ptr::operator =
  136.345 ms  113.144 ms        5536  AppendNode
  103.459 ms    8.522 ms        3742  std::__shared_ptr::operator =
   86.975 ms   13.870 ms        3194  std::__shared_count::operator =
    6.337 ms    1.802 ms         227  std::uniform_int_distribution::operator ()
    4.518 ms    1.129 ms         158  std::_Sp_counted_base::_M_add_ref_copy
    2.451 ms    2.451 ms          72  std::__shared_ptr::operator ->
    1.657 ms    1.657 ms          45  std::__shared_ptr::operator (cast)
    1.441 ms  323.637 us          43  std::__shared_count::__shared_count

```

* Significant difference in using `references` vs `copied return values`. This is the result from `copied return values`. 

```
   Avg total   Min total   Max total  Function
  ==========  ==========  ==========  ====================================
    1.632  s    1.632  s    1.632  s  main
   13.778 ms   13.778 ms   13.778 ms  operator <<
    1.163 ms   10.005 us    1.555  s  SortList
  129.409 us   10.876 us   10.540 ms  std::_List_base::_M_clear
  128.851 us   14.531 us   86.256 ms  mergeTwoSortedList
   56.177 us   10.221 us   10.558 ms  std::_List_base::~_List_base
   52.434 us   10.033 us   10.558 ms  std::list::~list
   45.062 us   10.011 us    1.173 ms  std::advance
   40.371 us   15.435 us  260.952 us  std::operator <<
   36.302 us   12.782 us  127.192 us  std::basic_ostream::operator <<
   22.669 us   12.203 us  214.176 us  std::_List_const_iterator::_M_const_cast
   21.192 us   21.192 us   21.192 us  std::ios_base::Init::~Init
   20.421 us   10.009 us   70.491 us  std::_List_base::_S_distance
   20.410 us   10.034 us  217.532 us  std::list::splice
   20.279 us   10.065 us  163.102 us  std::list::list
   20.039 us   10.550 us  162.227 us  std::_List_base::_M_init
   19.742 us   10.002 us  255.791 us  std::list::push_back
   19.432 us   10.013 us  233.603 us  std::list::pop_front
   19.393 us   10.000 us  217.334 us  std::list::_M_insert
   19.286 us   10.030 us  248.022 us  std::list::end
```
