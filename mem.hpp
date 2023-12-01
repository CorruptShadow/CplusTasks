#pragma once

namespace __hidden {
int mem_cur = 0;
int mem_max = 0;
}  // namespace __hidden

class MemTest {
  char dummy;

 public:
  static int current() { return __hidden::mem_cur; }
  static int peak() { return __hidden::mem_max; }

  MemTest() {
    // static_assert(sizeof(MemTest) == 1);
    ++__hidden::mem_cur;
    if (__hidden::mem_cur > __hidden::mem_max)
      __hidden::mem_max = __hidden::mem_cur;
  }
  MemTest(MemTest const &) : MemTest() {}
  MemTest(MemTest const &&) : MemTest() {}

  MemTest &operator=(MemTest const &) { return *this; };
  MemTest &operator=(MemTest const &&) { return *this; };

  ~MemTest() { --__hidden::mem_cur; }
};