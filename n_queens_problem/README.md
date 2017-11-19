## Use`UFTRACE` on N-Queens Problem

In CppCon 2017, a [talk](https://www.youtube.com/watch?v=s0B8hV2O8ps) about `uftrace` was presented. It can trace functions in user program as well as kernel. Use this to test the different ways of implementations on [N-Queens problem](https://en.wikipedia.org/wiki/Eight_queens_puzzle).

### Getting Started

`uftrace` can be found [here](https://github.com/namhyung/uftrace).
`g++` is used with option `-pg` to enable `uftrace <commands> <options>`
Some of the code requires `-std=c++17`, so `g++` must be sufficiently up to date.

### Running the tests

Run the following commands to use uftrace:
```
g++ -pg -std=c++17 -o nQueens nQueens.cpp
uftrace record nQueens
uftrace report --avg-total -t 20us -N ^_ -N ^std::__
uftrace graph -t 20us -N ^_ -N ^std::__
```
The current version will produce the following output:

```
# Function Call Graph for 'main' (session: a5cd9e4a733281b1)
=============== BACKTRACE ===============
 backtrace #0: hit 1, time   4.221 ms
   [0] main (0x40118d)

========== FUNCTION CALL GRAPH ==========
   4.221 ms : (1) main
   3.997 ms :  +-(1) getQueensPlaced
   3.986 ms :  | (1) getQueensPlacedSolution
   3.953 ms :  | (6) getQueensPlacedSolution
  21.965 us :  |  +-(1) std::vector::push_back
  21.742 us :  |  | (1) std::vector::_M_emplace_back_aux
            :  |  | 
   3.789 ms :  |  +-(20) getQueensPlacedSolution
   3.291 ms :  |     +-(36) getQueensPlacedSolution
   2.396 ms :  |     | (46) getQueensPlacedSolution
   1.203 ms :  |     |  +-(40) getQueensPlacedSolution
 107.849 us :  |     |  |  +-(3) getQueensPlacedSolution
 107.115 us :  |     |  |  | (3) std::vector::emplace_back
 105.616 us :  |     |  |  | (3) std::vector::_M_emplace_back_aux
            :  |     |  |  | 
  46.868 us :  |     |  |  +-(1) std::vector::pop_back
  46.556 us :  |     |  |    (1) std::allocator_traits::destroy
            :  |     |  | 
  24.990 us :  |     |  +-(1) std::vector::push_back
  24.710 us :  |     |    (1) std::allocator_traits::construct
            :  |     | 
  45.591 us :  |     +-(1) valid
            :  | 
 203.200 us :  +-(1) printAll
 193.208 us :  | (4) print
  23.224 us :  | (1) std::operator <<
            :  | 
  20.128 us :  +-(1) std::vector::~vector

```


### Test different implementations

[Rosetta Code.org](https://rosettacode.org/mw/index.php?title=N-queens_problem&redirect=no) has many different implementations of this same problem. I have used an implementation in C++ for a comparison. Here is the result:


```
My version:
$ uftrace report --avg-total -t 100us -N ^_ -N ^std::__
   Avg total   Min total   Max total  Function
  ==========  ==========  ==========  ====================================
   81.583 ms   81.583 ms   81.583 ms  main
   76.154 ms   76.154 ms   76.154 ms  getQueensPlaced
    5.070 ms    5.070 ms    5.070 ms  printAll
  516.978 us  100.049 us   76.144 ms  getQueensPlacedSolution
  364.340 us  109.154 us  738.010 us  std::vector::emplace_back
  363.819 us  108.644 us  737.470 us  std::vector::_M_emplace_back_aux
  356.819 us  356.819 us  356.819 us  std::vector::~vector
  233.908 us  233.908 us  233.908 us  std::basic_ostream::operator <<
  232.922 us  232.922 us  232.922 us  std::endl
  221.421 us  109.392 us  354.143 us  std::_Destroy
  221.011 us  109.116 us  353.563 us  std::_Destroy_aux::__destroy
  176.141 us  101.022 us  304.076 us  print
  164.861 us  164.861 us  164.861 us  std::vector::operator []
  149.427 us  111.956 us  169.018 us  valid
  126.070 us  111.630 us  152.069 us  std::vector::push_back
  125.814 us  111.369 us  151.790 us  std::allocator_traits::construct
  111.798 us  111.798 us  111.798 us  std::forward
  108.295 us  108.295 us  108.295 us  std::vector::pop_back
  106.835 us  106.835 us  106.835 us  std::allocator_traits::destroy

Rosetta version:
$ uftrace report --avg-total -t 100us -N ^_ -N ^std::__
   Avg total   Min total   Max total  Function
  ==========  ==========  ==========  ====================================
   91.724 ms   91.724 ms   91.724 ms  main
   83.393 ms   83.393 ms   83.393 ms  queens::queens
    3.997 ms  352.431 us    7.642 ms  operator <<
  686.781 us  686.781 us  686.781 us  queens::~queens
  686.553 us  686.553 us  686.553 us  std::set::~set
  686.333 us  686.333 us  686.333 us  std::_Rb_tree::~_Rb_tree
  375.391 us  126.621 us  685.047 us  std::_Rb_tree::_M_erase
  262.118 us  262.118 us  262.118 us  std::operator <<
  130.953 us  130.953 us  130.953 us  queens::ok
  119.589 us  109.733 us  125.413 us  std::mismatch
  117.638 us  100.021 us  225.129 us  std::set::insert
  116.923 us  100.019 us  223.888 us  std::_Rb_tree::_M_insert_unique
  116.053 us  100.033 us  222.369 us  std::_Rb_tree::_M_get_insert_unique_pos
  114.312 us  101.544 us  128.592 us  std::less::operator ()
  114.071 us  101.297 us  128.355 us  queens::solution_type::operator <
  104.575 us  104.575 us  104.575 us  std::_Rb_tree::_M_insert_
```
