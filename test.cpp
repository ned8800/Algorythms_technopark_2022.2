#include <iostream>
#include <string>
#include <limits>
using namespace std;

static constexpr size_t START_HEAP_CAPACITY = 8;

int main() {
    int *buf = new int[sizeof(int) * (START_HEAP_CAPACITY)];
    for(size_t i = 0; i < START_HEAP_CAPACITY; ++i) {
        buf[i] = 0;

    }
    return 0;
}
