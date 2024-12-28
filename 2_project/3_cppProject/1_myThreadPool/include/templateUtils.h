#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <utility>

// 通用模板，处理返回非 void 类型的函数
template <typename Func, typename... Args>
auto measureTime(Func &&func, Args &&...args) ->
    typename std::enable_if<!std::is_void<decltype(func(args...))>::value,
                            decltype(func(args...))>::type {
    auto start = std::chrono::high_resolution_clock::now();

    auto result = std::forward<Func>(func)(std::forward<Args>(args)...);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ns =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count();
    double duration_ms = duration_ns / 1'000'000.0;  // 将纳秒转换为毫秒

    std::cout << std::fixed << std::setprecision(6)
              << "Execution time: " << duration_ms << " ms\n";
    return result;
}

// 特化模板，处理返回 void 类型的函数
template <typename Func, typename... Args>
auto measureTime(Func &&func, Args &&...args) ->
    typename std::enable_if<std::is_void<decltype(func(args...))>::value,
                            void>::type {
    auto start = std::chrono::high_resolution_clock::now();

    std::forward<Func>(func)(std::forward<Args>(args)...);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ns =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count();
    double duration_ms = duration_ns / 1'000'000.0;  // 将纳秒转换为毫秒

    std::cout << std::fixed << std::setprecision(6)
              << "Execution time: " << duration_ms << " ms\n";
}