## Use`UFTRACE` to compare `std::sort` vs `heap_sort`


In CppCon 2017, a [talk](https://www.youtube.com/watch?v=s0B8hV2O8ps) about `uftrace` was presented. It looked like a perfect tool to test how fast an implementation of an algorithm is. To test the idea, I compared a `heap_sort` vs `std::sort`.

### Getting Started

`uftrace` can be found [here](https://github.com/namhyung/uftrace).
`g++` is used with option `-pg` to enable `uftrace <commands> <options>`

### Running the tests

Run the following commands to use uftrace:
```
g++ -pg -o sortAlmostSorted sortAlmostSorted.cpp
uftrace record sortAlmostSorted
uftrace report --avg-total -t 10us -N ^_ -N ^std::__
```
The current version will produce the following output:

```
$ uftrace report --avg-total -t 30us -N ^_ -N ^std::__
   Avg total   Min total   Max total  Function
  ==========  ==========  ==========  ====================================
  881.056 ms  881.056 ms  881.056 ms  main
  624.160 ms  624.160 ms  624.160 ms  heap_sort
  233.180 ms  233.180 ms  233.180 ms  std::sort
   50.087 us   30.340 us   65.283 us  std::vector::_M_emplace_back_aux
   48.821 us   48.821 us   48.821 us  std::forward
   48.277 us   32.560 us   64.424 us  std::vector::emplace_back
   47.258 us   30.000 us  418.706 us  std::priority_queue::pop
   45.617 us   30.006 us  417.072 us  std::pop_heap
   45.220 us   30.548 us   65.494 us  std::vector::push_back
   42.467 us   35.778 us   49.156 us  std::vector::end
   41.169 us   31.122 us   55.766 us  std::allocator_traits::construct
   40.304 us   30.088 us  121.114 us  std::priority_queue::push
   40.129 us   30.083 us   88.237 us  std::push_heap
   36.305 us   36.305 us   36.305 us  std::move
   34.651 us   34.651 us   34.651 us  std::priority_queue::empty
   34.461 us   34.461 us   34.461 us  std::vector::empty
   30.062 us   30.062 us   30.062 us  std::vector::pop_back
```

### Takeaway

`std::sort` is about three times faster, as the above suggests. It's not a surprise, though its good to know the actual magnitude.

A number of interesting points:

* `std::vector<T>` actually calls on `::push_back` method, even when its default parameter is given. Some discussions were given in [stackoverflow](https://stackoverflow.com/questions/47144488/vectortpush-back-is-used-on-predefined-constructor). It does not make much difference, in terms of speed, whether I give a `parameter` in the `constructor` calls to `std::vector<T>`.
* Sorting `std::array<T>` takes about 1/3 of time relative to that of `std::vector<T>`.
* `g++ -std=c++17` makes a difference, so use whenever possible. For example, this is the difference one sees when using `-std=c++17` option.
    
```
Without -std=c++17
   Avg total   Min total   Max total  Function
  ==========  ==========  ==========  ====================================
  847.306 ms  847.306 ms  847.306 ms  main
  595.876 ms  595.876 ms  595.876 ms  heap_sort
  228.033 ms  228.033 ms  228.033 ms  std::sort
   44.333 us   10.403 us  187.321 us  std::priority_queue::pop
   42.521 us   10.185 us  185.861 us  std::pop_heap
   18.602 us   16.979 us   20.226 us  std::equal
   18.415 us   10.334 us   53.470 us  std::vector::emplace_back
   18.391 us   10.075 us   87.701 us  std::vector::empty
   18.383 us   10.058 us   87.896 us  std::priority_queue::empty

With -std=c++17
   Avg total   Min total   Max total  Function
  ==========  ==========  ==========  ====================================
  822.566 ms  822.566 ms  822.566 ms  main
  580.189 ms  580.189 ms  580.189 ms  heap_sort
  219.482 ms  219.482 ms  219.482 ms  std::sort
   43.275 us   10.033 us  160.213 us  std::priority_queue::pop
   41.563 us   11.292 us  158.624 us  std::pop_heap
   21.364 us   19.960 us   22.769 us  std::equal
   20.059 us   10.795 us   59.117 us  std::priority_queue::empty
   20.034 us   10.640 us   58.923 us  std::vector::empty
   19.363 us   14.921 us   62.467 us  std::priority_queue::top
   19.217 us   14.957 us   62.248 us  std::vector::front
   19.013 us   12.220 us   52.842 us  std::forward
   18.911 us   18.813 us   19.010 us  std::_Destroy
   18.862 us   11.375 us   56.791 us  std::vector::emplace_back
   18.764 us   10.083 us   78.006 us  std::vector::push_back
   18.747 us   10.020 us   61.799 us  std::vector::begin

Using std::array<T> instead of std::vector<T>
   Avg total   Min total   Max total  Function
  ==========  ==========  ==========  ====================================
   87.071 ms   87.071 ms   87.071 ms  main
   79.831 ms   79.831 ms   79.831 ms  std::sort
   17.175 us   10.560 us   57.640 us  std::array::operator []
   17.120 us   14.572 us   23.063 us  rand
   12.865 us   12.865 us   12.865 us  std::ios_base::Init::~Init
```
