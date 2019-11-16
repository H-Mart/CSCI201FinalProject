#include "dynamic_array.h"

int main() {
    auto a = new DynamicArray<int>(2);
    for (long long i = 0; i < 200000000; i++) {
        a->push(i);
    }
        std::cout << "done" << std::endl;

    for (long long i = 0; i < 200000000; i++) {
        a->push(1);
        a->pop();
    }

    delete a;
    return 0;
}