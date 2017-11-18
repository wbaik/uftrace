## Use`UFTRACE` to compare `std::sort` vs `heap_sort`


In CppCon 2017, a [talk](https://www.youtube.com/watch?v=s0B8hV2O8ps) about `uftrace` was presented. It looked like a perfect tool to test how fast an implementation of an algorithm is.

### Getting Started

`uftrace` can be found [here](https://github.com/namhyung/uftrace).
`g++` is used with option `-pg` to enable `uftrace <commands> <options>`
