// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <cassert>
#include <type_traits>
#include <utility>

using namespace std;

template <typename T>
void test_swap(T left_val, T right_val) {
    T left  = left_val;
    T right = right_val;
    
    swap(left, right);
    assert(left == right_val);
    assert(right == left_val);
}

template <typename T>
void test_self_swap(T val) {
    T x = val;
    swap(x, x);
    assert(x == val); // self-swap should be a no-op
}

void test_integral_types() {
    // Test integral types
    test_swap<int>(42, 17);
    test_swap<char>('a', 'z');
    test_swap<unsigned long>(1000UL, 2000UL);
    test_swap<short>(100, -100);
    
    // Test self-swap for integral types
    test_self_swap<int>(42);
    test_self_swap<char>('x');
    test_self_swap<unsigned long>(1000UL);
    test_self_swap<short>(100);
}

void test_non_integral_types() {
    // Test floating point types
    test_swap<float>(3.14f, 2.718f);
    test_swap<double>(1.414, 1.732);
    
    // Test pointer types
    int a = 1, b = 2;
    test_swap<int*>(&a, &b);
    
    // Test self-swap for non-integral types
    test_self_swap<float>(3.14f);
    test_self_swap<double>(1.414);
    test_self_swap<int*>(&a);
}

int main() {
    test_integral_types();
    test_non_integral_types();
}
