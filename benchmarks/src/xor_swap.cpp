// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <algorithm>
#include <benchmark/benchmark.h>
#include <cstddef>
#include <cstdint>
#include <type_traits>

using namespace std;

template <class T, template <class> class Padder>
void std_swap_xor_enabled(benchmark::State& state) {
    static_assert(is_integral_v<T>, "Type must be integral");
    Padder<T> padded_a;
    auto& a = padded_a.value;
    a = T{0x55}; // Pattern 0101 0101
    Padder<T> padded_b;
    auto& b = padded_b.value;
    b = T{0xAA}; // Pattern 1010 1010

    for (auto _ : state) {
        swap(a, b);
        benchmark::DoNotOptimize(a);
        benchmark::DoNotOptimize(b);
    }
}

template <class T, template <class> class Padder>
void std_swap_xor_disabled(benchmark::State& state) {
    static_assert(is_integral_v<T>, "Type must be integral");
    Padder<T> padded_a;
    auto& a = padded_a.value;
    a = T{0x55}; // Pattern 0101 0101
    Padder<T> padded_b;
    auto& b = padded_b.value;
    b = T{0xAA}; // Pattern 1010 1010

    for (auto _ : state) {
        T tmp = move(a);
        a = move(b);
        b = move(tmp);
        benchmark::DoNotOptimize(a);
        benchmark::DoNotOptimize(b);
    }
}

// Test uint8_t
BENCHMARK(std_swap_xor_enabled<uint8_t, highly_aligned>);
BENCHMARK(std_swap_xor_disabled<uint8_t, highly_aligned>);
BENCHMARK(std_swap_xor_enabled<uint8_t, not_highly_aligned>);
BENCHMARK(std_swap_xor_disabled<uint8_t, not_highly_aligned>);

// Test uint16_t
BENCHMARK(std_swap_xor_enabled<uint16_t, highly_aligned>);
BENCHMARK(std_swap_xor_disabled<uint16_t, highly_aligned>);
BENCHMARK(std_swap_xor_enabled<uint16_t, not_highly_aligned>);
BENCHMARK(std_swap_xor_disabled<uint16_t, not_highly_aligned>);

// Test uint32_t
BENCHMARK(std_swap_xor_enabled<uint32_t, highly_aligned>);
BENCHMARK(std_swap_xor_disabled<uint32_t, highly_aligned>);
BENCHMARK(std_swap_xor_enabled<uint32_t, not_highly_aligned>);
BENCHMARK(std_swap_xor_disabled<uint32_t, not_highly_aligned>);

// Test uint64_t
BENCHMARK(std_swap_xor_enabled<uint64_t, highly_aligned>);
BENCHMARK(std_swap_xor_disabled<uint64_t, highly_aligned>);
BENCHMARK(std_swap_xor_enabled<uint64_t, not_highly_aligned>);
BENCHMARK(std_swap_xor_disabled<uint64_t, not_highly_aligned>);

BENCHMARK_MAIN();
