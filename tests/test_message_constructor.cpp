#include "MessageConstructor.h"

#include <cassert>
#include <iostream>

int main() {
    const MessageConstructor constructor;

    assert(constructor.constructMessageAt(1000) == "@#<1000>##@");
    assert(constructor.constructMessageAt(1000, "hello") == "@#<1000>#&hello#@");
    assert(constructor.constructMessageAt(42, 'A', true, -7, 25.5) == "@#<42>#&A&1&-7&25.5#@");
    assert(constructor.constructMessageAt(5, "A&B", "x#y", "c\\d") ==
           "@#<5>#&A\\&B&x\\#y&c\\\\d#@");

    std::cout << "All MessageConstructor tests passed.\n";
    return 0;
}
