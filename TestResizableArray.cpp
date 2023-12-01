#include <cstdio>
#include <string>

#include "ResizableArray.hpp"
#include "mem.hpp"

// tests allocated objects
// returns true if test failed, false otherwise
bool runTest(std::string introMessage, int expectedAllocation,
             std::string failureMessage = "======== Failed... ========",
             std::string successMessage = "======== Success! ========") {
  printf("%s", introMessage.c_str());
  printf("\n");
  printf("Expected allocation: %i\n", expectedAllocation);
  int currentAllocation = MemTest::current();
  printf("Measured allocation: %i\n", currentAllocation);
  if (currentAllocation == expectedAllocation) {
    printf("%s", successMessage.c_str());
    printf("\n");
    printf("\n");
    return false;
  } else {
    printf("%s", failureMessage.c_str());
    printf("\n");
    printf("\n");
    return true;
  }
}

int main() {
  ResizableArray<MemTest> array;
  bool errorDetected = false;

  // init
  errorDetected |= runTest("Testing initialization", 4);

  for (int i = 0; i < 20; i++) array.push_back(MemTest());
  errorDetected |= runTest("Testing after first fill", 32);

  for (int i = 0; i < 10; i++) array.pop_back();
  errorDetected |= runTest("Testing with 10 elements left", 32);

  // first resize
  for (int i = 0; i < 2; i++) array.pop_back();
  errorDetected |= runTest("Testing with 8 elements left", 32);

  array.pop_back();
  errorDetected |= runTest("Testing with 7 elements left", 16);

  array.pop_back();
  errorDetected |= runTest("Testing with 6 elements left", 16);

  // second resize
  for (int i = 0; i < 2; i++) array.pop_back();
  errorDetected |= runTest("Testing with 4 elements left", 16);

  array.pop_back();
  errorDetected |= runTest("Testing with 3 elements left", 8);

  array.pop_back();
  errorDetected |= runTest("Testing with 2 elements left", 8);

  // final elements
  array.pop_back();
  errorDetected |= runTest("Testing with 1 element left", 4);

  array.pop_back();
  errorDetected |= runTest("Testing with 0 elements left", 4);

  if (errorDetected) {
    printf("At least one test case failed!\n");
  } else {
    printf("All of these test cases passed.\n");
  }
  printf("\n");

  return 0;
}