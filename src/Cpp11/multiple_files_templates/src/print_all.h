#pragma once

template<typename T, typename... Args>
void print_all(T arg, Args&&... args);
void print_all();
int sum(const int a, const int b);

#include "print_all.tpp"
