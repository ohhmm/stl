// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <cassert>
#include <cstdint>
#include <type_traits>
#include <utility>

using namespace std;

template <typename T>
void test_integral_swap() {
    static_assert(is_integral_v<T>, "T must be an integral type");

    // Test distinct values
    {
        T a = static_cast<T>(42);
        T b = static_cast<T>(100);
        T original_a = a;
        T original_b = b;

        swap(a, b);
        assert(a == original_b);
        assert(b == original_a);

        // Swap back
        swap(a, b);
        assert(a == original_a);
        assert(b == original_b);
    }

    // Test self-swap
    {
        T a = static_cast<T>(42);
        T& ref_a = a;
        swap(a, ref_a);
        assert(a == static_cast<T>(42)); // Value should remain unchanged
    }

    // Test adjacent values
    {
        T a = static_cast<T>(5);
        T b = static_cast<T>(6);
        swap(a, b);
        assert(a == static_cast<T>(6));
        assert(b == static_cast<T>(5));
    }
}

// Test non-integral types to ensure they still work
void test_non_integral_swap() {
    // Test with floating point
    {
        float a = 3.14f;
        float b = 2.718f;
        swap(a, b);
        assert(a == 2.718f);
        assert(b == 3.14f);
    }

    // Test with pointers
    {
        int x = 1, y = 2;
        int* a = &x;
        int* b = &y;
        int* original_a = a;
        int* original_b = b;
        swap(a, b);
        assert(a == original_b);
        assert(b == original_a);
    }
}

int main() {
    // Test all integral types
    test_integral_swap<char>();
    test_integral_swap<signed char>();
    test_integral_swap<unsigned char>();
    test_integral_swap<short>();
    test_integral_swap<unsigned short>();
    test_integral_swap<int>();
    test_integral_swap<unsigned int>();
    test_integral_swap<long>();
    test_integral_swap<unsigned long>();
    test_integral_swap<long long>();
    test_integral_swap<unsigned long long>();

    // Verify non-integral types still work
    test_non_integral_swap();
}
